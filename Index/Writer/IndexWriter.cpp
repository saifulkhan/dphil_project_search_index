#include "IndexWriter.h"

IndexWriter::IndexWriter()
{
     curBufferDoc = 0;
     bufferDoc = 100;
}

IndexWriter::~IndexWriter()
{
   this->close();
}

void IndexWriter::open( const char * filepath, bool create )
{
    cout << "IndexWriter, creating cache on: " << filepath << endl;
    m_strPath = string(filepath);        // TODO: Check filepath exists, else create, then append "/" ate the end.
    int len = strlen( filepath ) + 5;
    path = new char[len];
    strcpy( path, filepath );

    isCreate = create;
    docCount = 0;
    fieldCount = 0;
    termCount = 0;

    // segment
    p_segment = new char[len + 20];
    strcpy( p_segment, filepath );
    strcat( p_segment, "segments" );

    indexName = new char[10];
    if ( create )
        strcpy( indexName, "1" );
    else
        getSegName( indexName );
    strcat( path, indexName );


//	if(!create)
//		loadsegments();
    initSegment( create );
	
    // tii
    p_tii = new char[len+20];
    strcpy( p_tii, path );
    strcat( p_tii, ".tii" );
    p_tiiOutput = new IndexOutput( p_tii, true );
    p_tiiOutput->writeLong(0);

    // del
    p_del = new char[len+20];
    strcpy( p_del, path );
    strcat( p_del, ".del" );
    p_delOutput = new IndexOutput( p_del, true );
	p_delOutput->writeLong(0);
#ifdef DBG_CACHE
    cout << __PRETTY_FUNCTION__ << "Del path: " << p_del << endl;
#endif
    // pro
    p_pro = new char[len+20];
    strcpy( p_pro, path );
    strcat( p_pro, ".pro" );
    p_proOutput = new IndexOutput( p_pro, true );

    // fdi
    p_fdi = new char[len+20];
    strcpy( p_fdi, path );
    strcat( p_fdi, ".fdi" );
    //if (!create)
    //loadfdi(p_fdi);
    p_fdiOutput = new IndexOutput( p_fdi, true );
	//if (create)
    p_fdiOutput->writeLong(0);  //First, write the total number of the first to write 0 overlying etc. back to the beginning and then finished

    // fdt
    p_fdt = new char[len+20];
    strcpy( p_fdt, path );
    strcat( p_fdt, ".fdt" );
    p_fdtOutput = new IndexOutput( p_fdt, true );

    // fmn
    p_fmn = new char[len+20];
    strcpy( p_fmn, filepath );
    strcat( p_fmn, "seg.fmn" );
    if ( !create )                                  // Old index
        loadfmn( p_fmn );
    p_fmnOutput = new IndexOutput( p_fmn, create );
    if ( create )                                   // New index
		p_fmnOutput->writeInt(0);
}


/*
 * Read the segment file and get the last segment name
 * The new segment name is last segment name + 1
 */

void IndexWriter::getSegName( char *name )
{
    IndexInput segInput( p_segment );
    int32_t segCount = segInput.readInt();
#ifdef DBG_CACHE
    cout << __PRETTY_FUNCTION__ << "IndexInput the segment: " << p_segment << ", segCount= " << segCount << endl;
#endif
    for ( int i = 0; i < segCount; i++ ) {
        string segName;
        segInput.readString( segName );
#ifdef DBG_CACHE
        cout << __PRETTY_FUNCTION__ << "segName= " << segName << endl;
#endif
        int32_t status = segInput.readVint();

        if( i == (segCount - 1) ) {
            int32_t  lastName = atoi( segName.c_str() );
            lastName++;
            sprintf( name, "%d", lastName );
#ifdef DBG_CACHE
            cout << __PRETTY_FUNCTION__ << "new name= " << name << endl;
#endif
        }
    }
}


/*
 * If create, then write segment count = 1, name = "1" ...
 * Else, increment the segment count at the beggining, and write new segment name at the bottom ...
 */

void IndexWriter::initSegment( bool create )
{
    IndexOutput segmentOutput( p_segment, create );

    if (!create) {                                      // Old index
        IndexInput segInput( p_segment );
        int32_t segCount = segInput.readInt();
        segCount = segCount + 1;                        // Increase segment count
        string segName( indexName );
        segmentOutput.writeString( segName );           // Write new segment name ~ new indexname
        segmentOutput.writeVint(SEGSTATUS_WRITE );
        segmentOutput.seek(0);
        segmentOutput.writeInt( segCount );             // Write segment count
    } else {                                            // New index by name
        segmentOutput.writeInt(1);
        string segName( "1" );
        segmentOutput.writeString( segName );
        segmentOutput.writeVint(SEGSTATUS_WRITE );
    }
}


/*
 * Read the seg.fnm file and copy the Field names.
 */

void IndexWriter::loadfmn( char *fmn )
{
    IndexInput *p_fmnInput = new IndexInput( fmn );
    fieldCount = p_fmnInput->readInt();
    for (int i = 0; i < fieldCount; i++ ) {
        Field *deF = new Field();
        p_fmnInput->readString( deF->name );
        deF->is_store = p_fmnInput->readVint();
        deF->token = p_fmnInput->readVint();
        deF->type = p_fmnInput->readVint();
        m_doc.addField( deF->name, deF );
    }
    delete p_fmnInput;
}


void IndexWriter::addDocument( Document &doc )
{    
    string docStr;

    // (?) Traversal, write the data file, and write on the position in the index file
    p_fdiOutput->writeLong( p_fdtOutput->getFilePointer() );

    // Iterate through all the fields of the document
    for ( map <string, Field*>::iterator it = doc.m_fieldMap.begin(); it != doc.m_fieldMap.end(); it++ )
    {

        Field *newField = (*it).second;

        // if m_doc does not contain the field information
        if ( !m_doc.containField( newField->name ) )
        {
            Field *deF    = new Field();
            deF->is_store = newField->is_store;
            deF->token    = newField->token;
            deF->type     = newField->type;
            deF->name     = newField->name;

            //fmn: Fields, stores information about fields.
            p_fmnOutput->writeString( deF->name );
            p_fmnOutput->writeVint( deF->is_store );
            p_fmnOutput->writeVint( deF->token );
            p_fmnOutput->writeVint( deF->type );
            m_doc.addField( deF->name, deF );
            fieldCount++;
        }


        // Do not store, then skip
        if ( (newField->is_store) == STORE_NO )
            continue;

        // Write the field data in .fdt and concatinate all the field data in docStr
        switch (newField->type)
        {
            case STORE_VINT:
                p_fdtOutput->writeVint( atoi( newField->data.c_str() ) );
                break;

            case STORE_INT:
                p_fdtOutput->writeInt( atoi( newField->data.c_str() ) );
                break;

            case STORE_LONG:
                p_fdtOutput->writeLong(atoi(newField->data.c_str()));
                break;

            case STORE_VLONG:
                p_fdtOutput->writeVlong(atoi(newField->data.c_str()));
                break;

            case STORE_STRING:
                p_fdtOutput->writeString(newField->data);
                break;

            default:
                break;
        }

        if (newField->token == STORE_KEYWORD)
            docStr = docStr + " " + newField->data;

    } // for, finished iterating the fields, and concatenating the field data in docStr

    // Parse the field data which is a concatenated string, docStr, to get the terms and its corresponding frequency map
    m_tokeniser.tokenise(docStr);
    map <string, int> termMap = m_tokeniser.getTermMap();

    // Popolate the termMap_m : <term, <docid, frequency> >
    // termMap : map<string, int32_t>, TODO: should we call it freqMap
    for ( map<string, int32_t>::iterator it = termMap.begin(); it != termMap.end(); it++ )
    {
        if ( m_termMap.find( it->first ) == m_termMap.end() )
        {
            map <int64_t, int32_t> docMap;
            docMap[docCount] = it->second;
            m_termMap[it->first] = docMap;
            termCount++;
        } else
        {
            m_termMap[it->first][docCount] = it->second;
        }
        // cout << __PRETTY_FUNCTION__ << it->first << ": " << it->second << endl;
    } // for

    curBufferDoc++;
    docCount++;
}


void IndexWriter::close()
{
    flush();

    p_fdiOutput->seek(0);
    p_fdiOutput->writeLong(docCount);
    p_fmnOutput->seek(0);
    p_fmnOutput->writeInt(fieldCount);
    p_tiiOutput->seek(0);
    p_tiiOutput->writeLong(termCount);

    delete []p_segment;
    delete []path;
    delete []p_tii;
    delete []p_fdi;
    delete []p_fdt;
    delete []p_fmn;
    delete []p_pro;
    delete []p_del;

    delete []indexName;
    delete p_fdiOutput;
    delete p_proOutput;
    delete p_fdtOutput;
    delete p_fmnOutput;
    delete p_tiiOutput;
    delete p_delOutput;

    // close  all the files before merging, else it wiull give runtime error
    IndexMerge merge;
    merge.open( (char*)m_strPath.c_str() );
    merge.merge();
}


/*
 * Write the terms in .tii, and map <document and correcponding frequency> in .pro
 * Then the offset to .pro is written in .tii
 */

void IndexWriter::flush()
{
    //	if (curBufferDoc>=bufferDoc) {

    // .tii
    for ( map <string, map <int64_t, int32_t> >::iterator it = m_termMap.begin(); it != m_termMap.end(); it++ ) {
        string s = it->first;
        map <int64_t, int32_t> tMap = it->second;
        p_tiiOutput->writeString( s );                                // Key value
        p_tiiOutput->writeVlong( p_proOutput->getFilePointer() );     // Write file offset pointer
#ifdef DBG_CACHE
        cout << "tii: " << it->first << ":" << p_proOutput->getFilePointer() << endl;
#endif
         // pro
        p_proOutput->writeVint( tMap.size() );                        // Posts
        for ( map <int64_t, int32_t>::iterator tit = tMap.begin(); tit != tMap.end(); tit++) {
            p_proOutput->writeVlong( tit->first );                    // Writing numbers
            p_proOutput->writeVint( tit->second );                    // Frequency
#ifdef DBG_CACHE
            cout << "pro: " << tit->first << ":" << tit->second << endl;
#endif
        }
    }
    //	}
    m_termMap.clear();

    writeSegment();
}


/*
 * Update the status of the segment named indexName as SEGSTATUS_CLOSE
 */

void IndexWriter::writeSegment()
{
    map <string, int32_t> m_segmentMap;
    loadsegments( m_segmentMap );
    IndexOutput segmentOutput( p_segment, true );
    segmentOutput.writeInt( m_segmentMap.size() );

    for ( map <string, int32_t>::iterator it = m_segmentMap.begin(); it != m_segmentMap.end(); it++ ) {
        string segName = it->first;
        int32_t status = it->second;
        //cout << __PRETTY_FUNCTION__ << "Segment Name: " << segName << ", Status: " << status << ", indexName: " << indexName;
        segmentOutput.writeString( segName );
        if ( strcmp( segName.c_str(), indexName ) == 0 )
              segmentOutput.writeVint( SEGSTATUS_CLOSE );
        else
             segmentOutput.writeVint(status);
    }
}


/*
 * Read the segments file to a map <segment name and status>
 */

void IndexWriter::loadsegments( map <string, int32_t> &m_segmentMap )
{
    IndexInput segInput( p_segment );
    int32_t segCount = segInput.readInt();          // Total segments

    for ( int i = 0; i < segCount; i++ ) {
        string segName;
        segInput.readString( segName );
        int32_t status = segInput.readVint();
        m_segmentMap[segName] = status;
	}
}


/*
 * None of the below functions are used.
 */

void IndexWriter::loadtii(char *tii)
{

}


//void IndexWriter::loadDel(char *del)
// {
//	IndexInput *p_delInput = new IndexInput(del);
//	int64_t delCount = p_delInput->readLong();
//	for( int i = 0; i < delCount; i++ ) {
//		int64_t docid = p_delInput.readVlong();
//		m_delVo.push_back( docid );
//	}
//	delete p_delInput;
//}


void IndexWriter::loadfdi(char *fdi)
{
	IndexInput *p_fdiInput=new IndexInput(fdi);
	docCount=p_fdiInput->readLong();
	delete p_fdiInput;
}


void IndexWriter::setBufferDoc(int64_t num)
{
    bufferDoc = num;
}

