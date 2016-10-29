#include "IndexMerge.h"

IndexMerge::IndexMerge()
{
}


IndexMerge::IndexMerge( char *path )
{
    open( path );
}


IndexMerge::~IndexMerge()
{

}


void IndexMerge::open( char *path )
{
    m_path.assign( path );
    m_segmentInfos.load( path) ;
	loadfmn();
}


void IndexMerge::loadfmn()
{
    int len = m_path.length();
	char fmn[len+10];
    strcpy( fmn, m_path.c_str() );
    strcat( fmn, "seg.fmn" );
    IndexInput *p_fmnInput = new IndexInput( fmn );
    int32_t fieldCount = p_fmnInput->readInt();

    for ( int i = 0; i < fieldCount; i++ ) {
        Field *deF = new Field();
        p_fmnInput->readString( deF->name );
        deF->is_store = p_fmnInput->readVint();
        deF->token = p_fmnInput->readVint();
        deF->type = p_fmnInput->readVint();
        m_doc.addField( deF->name, deF );
	}
	delete p_fmnInput;
}


/*
 *
 *
 *
 */

void IndexMerge::merge()
{
    int len = m_path.length();
    char newPath[len+10];
    strcpy( newPath, m_path.c_str() );
    strcat( newPath, m_segmentInfos.getNextSegName().c_str() );

    // fdi, the new merged fdi
    char fdiPath[len+10];
    strcpy( fdiPath, newPath );
    strcat( fdiPath, ".fdi" );
    IndexOutput fdiOutput( fdiPath, true );
    char fdtPath[len+10];
    strcpy( fdtPath, newPath );
    strcat( fdtPath, ".fdt" );
    IndexOutput fdtOutput( fdtPath, true );
    fdiOutput.writeLong( m_segmentInfos.m_docCount );  // Total doc write

    // tii, combined tii
    char tiiPath[len+10];
    strcpy( tiiPath, newPath );
    strcat( tiiPath, ".tii" );
    IndexOutput tiiOutput( tiiPath, true );

    // Combined del
    char delPath[len+10];
    strcpy( delPath, newPath );
    strcat( delPath, ".del" );
    IndexOutput delOutput( delPath, true );
    delOutput.writeLong(0);

    // pro, combined
    char proPath[len+10];
    strcpy( proPath, newPath );
    strcat( proPath, ".pro" );
    IndexOutput proOutput( proPath, true );
    proOutput.writeLong(0);


    map <string, IndexInput *> indexMap;            // pro
    map <string, map <string, int64_t> > termMap;   // tii
    map <string, vector <int64_t>  > delMap;        // del

    for ( map <string, Segment>::iterator it = m_segmentInfos.m_segMap.begin(); it != m_segmentInfos.m_segMap.end(); it++ ) {
        string segName = it->first;
        Segment segment = it->second;

        // open <segName>.pro, add in the map
        char inProPath[len + 10];
        strcpy( inProPath, m_path.c_str() );
        strcat( inProPath, segName.c_str() );
        strcat( inProPath, ".pro" );
        IndexInput *tProInput = new IndexInput( inProPath );
        indexMap[segName] = tProInput;

        // tii
        char inTiiPath[len + 10];
        strcpy( inTiiPath, m_path.c_str() );
        strcat( inTiiPath, segName.c_str() );
        strcat( inTiiPath, ".tii" );
        IndexInput tTiiInput( inTiiPath );
        loadTii( tTiiInput, termMap, segName );

        // del
        char inDelPath[len+10];
        strcpy( inDelPath, m_path.c_str() );
        strcat( inDelPath, segName.c_str() );
        strcat( inDelPath, ".del" );

#ifdef DBG_CACHE
        cout << __PRETTY_FUNCTION__ << "Loading del file: " << inDelPath << endl;
#endif
        IndexInput tDelInput( inDelPath );
        loadDel( tDelInput, delMap, segName );

        // Merge all the field data in <new>.fdt file
        // Write the pointer to <new>.fdi file
        char inFdtPath[len + 10];
        strcpy( inFdtPath, m_path.c_str() );
        strcat( inFdtPath, segName.c_str() );
        strcat( inFdtPath, ".fdt" );
        IndexInput tfdtInput( inFdtPath );

        for ( int64_t i = 0; i < segment.docCount; i++ ) {
            fdiOutput.writeLong( fdtOutput.getFilePointer() );   // fdi
            copyDoc( fdtOutput, tfdtInput );                     // fdt
        }
    }

    // update the new merged tii, pro
    // read the termMap data-structure and write to the new tii file
    // the total no of terms
    int64_t termCount = termMap.size();
    tiiOutput.writeLong( termCount );

    for ( map <string, map <string, int64_t> >::iterator it = termMap.begin(); it != termMap.end(); it++ ) {

        string tm = string( it->first );
        tiiOutput.writeString( tm );                            // the term
#ifdef DBG_CACHE
        cout << tm << endl;
#endif
        tiiOutput.writeVlong( proOutput.getFilePointer() );     // pointer to pro
        map <string, int64_t> segMap = it->second;
        int32_t docC = 0;

        // The total number of articles to the item
        for ( map <string, int64_t>::iterator segit = segMap.begin(); segit != segMap.end(); segit++ ) {
            IndexInput *indexInput = indexMap[segit->first];
            // cout << segit->first << endl;
            indexInput->seek( segit->second );
            docC += indexInput->readVint();
        }

        proOutput.writeVint(docC);

        for ( map <string, int64_t>::iterator segit = segMap.begin(); segit != segMap.end(); segit++ ) {
            IndexInput *in = indexMap[segit->first];
            in->seek( segit->second );
            int32_t cou = in->readVint();     // Read Posts
            Segment segment = m_segmentInfos.m_segMap[segit->first];  // Get section information
            for ( int j = 0; j < cou; j++ ) {
                    int64_t docId = in->readVlong();      // Read the old article ID
                    docId += segment.startNum;            // No new posts
                    int32_t pro = in->readVint();         // Word frequency
                    proOutput.writeVlong(docId);
                    proOutput.writeVint(pro);
            } // for
        } // for
    } // for - done with tii and pro

    // del
    int64_t delCount = 0;
    for ( map <string, vector <int64_t>  >::iterator it = delMap.begin(); it != delMap.end(); it++ ) {
        string segName = string( it->first );
        Segment segment = m_segmentInfos.m_segMap[segName];    // Get section information
        vector <int64_t> &delVo = it->second;

        for ( int i = 0; i < delVo.size(); i++ ) {
            int64_t delid = delVo[i];
            delid =+ segment.startNum;
            delOutput.writeVlong( delid );
            delCount++;
        }
    }
    delOutput.seek(0);
#ifdef DBG_CACHE
    cout << __PRETTY_FUNCTION__ << "Merged/new del file: " << delPath << ", delCount= " << delCount << endl;
#endif
    delOutput.writeLong( delCount );


    // Cleanup, and update the segment file which will now contain one final merged segment info

    for ( map <string, IndexInput*>::iterator it = indexMap.begin(); it != indexMap.end(); it++ ) {
        delete it->second;
    }
    indexMap.clear();
    termMap.clear();
    removeOldIndex();
    char segPath[len+10];
    strcpy( segPath, m_path.c_str() );
    strcat( segPath, "segments" );
    IndexOutput segOutput( segPath, true);    // Combined
    segOutput.writeInt( 1 );
    string newSeg = string( m_segmentInfos.getNextSegName() );
    segOutput.writeString( newSeg );
    segOutput.writeVint( SEGSTATUS_CLOSE );
}


/*
 * Craete a map of term, and segments where it appear and pointer- <term <segment name, pointer> >
 */

void IndexMerge::loadTii( IndexInput &tiiInput, map <string, map <string, int64_t> > &termMap, string segName )
{
    int64_t termCount = tiiInput.readLong();                // total number of terms in tii

    for ( int64_t i = 0; i < termCount; i++ ) {

        string term;
        tiiInput.readString( term );                        // Read term
        map <string, map <string, int64_t> >::iterator it = termMap.find( term );
        if ( it == termMap.end() ) {                        // term is not there in the termMap
            map <string, int64_t> segTermMap;
            segTermMap[segName] = tiiInput.readVlong();
            termMap[term] = segTermMap;
        } else {                                            // term is there in the termMap
            map <string, int64_t> segTermMap = it->second;
            segTermMap[segName] = tiiInput.readVlong();     // add the segment where the term re-appers and pointer
            termMap[term] = segTermMap;                     // update the termMap for that term. Note: map inside map
        }
    }
}


/*
 * Read all the segment name.del and craete a map <segment name, vector <doc#> >
 */

void IndexMerge::loadDel( IndexInput &delInput, map <string, vector <int64_t>  > &delMap, string segName )
{
    int64_t delCount = delInput.readLong();
#ifdef DBG_CACHE
    cout << __PRETTY_FUNCTION__ << "delCount= " << delCount << endl;
#endif
    vector <int64_t> delVector;
    for ( int64_t i = 0; i < delCount; i++ ) {
        delVector.push_back( delInput.readVlong() );
    }
    delMap[segName] = delVector;
}


/*
 * Reads field data from input and writes back to destFdt
 */

void IndexMerge::copyDoc( IndexOutput &destFdt, IndexInput &input )
{
    for ( map <string, Field *>::iterator it = m_doc.m_fieldMap.begin(); it != m_doc.m_fieldMap.end(); it++ ) {
        if ( (it->second)->is_store != STORE_YES )
			continue;

        switch ( (it->second)->type ) {
            case STORE_VINT:
                destFdt.writeVint( input.readVint() );
                break;

            case STORE_INT:
                destFdt.writeInt( input.readInt() );
                break;

            case STORE_LONG:
                destFdt.writeLong( input.readLong() );
                break;

            case STORE_VLONG:
                destFdt.writeVlong( input.readVlong() );
                break;

            case STORE_STRING: {
                string data;
                input.readString( data );
                destFdt.writeString( data );
                break;
            }

            default:
                break;
        } // switch
    } // for
}


/*
 * Deleted the old index files
 */

void IndexMerge::removeOldIndex()
{
    for ( map <string,Segment>::iterator it = m_segmentInfos.m_segMap.begin(); it != m_segmentInfos.m_segMap.end(); it++ ) {
        string segName = it->first;
        int len = m_path.length();
		char newPath[len+10];
        strcpy( newPath, m_path.c_str() );
        strcat( newPath, segName.c_str() );

        char tiiPath[len+10];
        strcpy( tiiPath, newPath );
        strcat( tiiPath,".tii" );
        remove( tiiPath );
		
		char fdiPath[len+10];
        strcpy( fdiPath,newPath );
        strcat( fdiPath, ".fdi" );
        remove( fdiPath );
		
		char fdtPath[len+10];
        strcpy( fdtPath, newPath );
        strcat( fdtPath, ".fdt" );
        remove( fdtPath );
		
		char proPath[len+10];
        strcpy( proPath, newPath );
        strcat( proPath, ".pro" );
        remove( proPath );
		
		char delPath[len+10];
		strcpy(delPath,newPath);
		strcat(delPath,".del");
		remove(delPath);
	}
}
