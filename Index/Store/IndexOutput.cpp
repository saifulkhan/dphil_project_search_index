#include "IndexOutput.h"

IndexOutput::IndexOutput()
{
	
}


IndexOutput::~IndexOutput()
{
    if (!isClose)
		close();
}


IndexOutput::IndexOutput(char * m_file, bool create)
{
    isClose = false;
    m_buffersize = 1024;
    m_bufferPos = 0;
    m_buffer = new char[m_buffersize];

    string str = string( "wb" );
    if (!create)
        str = string( "r+b" );  // file must exist

    if ( (fp = fopen( m_file, str.c_str() ) ) == NULL ) {
        cout << __PRETTY_FUNCTION__ << "Can not open file: " << m_file;
        assert( false );
    }

    if (!create)
        fseek( fp, 0, SEEK_END );  // obtain the file size
    m_bufferStart = ftell( fp );
}


void IndexOutput::close()
{
	this->flush();
	delete  m_buffer;
	fclose(fp);
    isClose = true;
}


// Writes an int in a variable-length format. Writes between one and five bytes.
// Smaller values take fewer bytes. Negative numbers are not supported.

void IndexOutput::writeVint( int32_t value )
{
    uint32_t ui = value;

    while( (ui & ~0x7f) != 0) {
        this->writeByte( (byte)((ui & 0x7f) | 0x80) );
        ui = ui >> 7;
    }
    this->writeByte( (byte)ui );
}


// Writes an long in a variable-length format. Writes between one and nine bytes.
// Smaller values take fewer bytes. Negative numbers are not supported.

void IndexOutput::writeVlong( int64_t value )
{
    uint64_t u = value;
    while( (u & ~0x7f) != 0) {
        this->writeByte( (byte)((u & 0x7f) | 0x80) );
        u = u >> 7;
    }
    this->writeByte( (byte)u );
}


void IndexOutput::writeLong(int64_t value)
{
    this->writeInt( (int32_t)(value>>32) );
    this->writeInt( (int32_t)value );
}


void IndexOutput:: writeInt( int32_t value )
{
	//for( int i=0;i<4;i++){
    writeByte( (byte)(value >> 24) );
    writeByte( (byte)(value >> 16) );
    writeByte( (byte)(value >> 8) );
    writeByte( (byte)(value) );
    //}
}


void IndexOutput::writeString( string  &str )
{
    int32_t len = str.length();
    this->writeVint( len );
    this->writeChars( str.c_str(), 0, len );
}


// Good tutorial about unicode: http://rise4fun.com/Bek/tutorial/utf8

void  IndexOutput::writeChars( const char *s, int64_t start, int64_t len )
{
    int64_t end = start + len;
    for ( int64_t i = start; i < end; i++ ) {

        int32_t code = (int32_t) s[i];

        if (code >= 0x01 && code <= 0x7F) {
            writeByte( (byte) code );
        } else if ( ((code >= 0x80) && (code <= 0x7FF)) || code == 0 ) {   // TODO: Fix later on, not quite correct
            writeByte( (byte) (0xC0 | (code >> 6)) );
            writeByte( (byte) (0x80 | (code & 0x3F)) );
        } else {
            writeByte( (byte) (0xE0 | (((int32_t) code) >> 12)) );
            writeByte( (byte) (0x80 | ((code >> 6) & 0x3F)) );
            writeByte( (byte) (0x80 | (code & 0x3F)) );
        }
    }
}


void IndexOutput::writeByte( byte  b )
{
    if (this->m_bufferPos >= this->m_buffersize)
		     this->flush();

    this->m_buffer[this->m_bufferPos++] = b;
}


int64_t  IndexOutput::getFilePointer()
{
    return ( m_bufferStart + (int64_t)m_bufferPos );
}


void IndexOutput::flush()
{
    this->m_bufferStart = this->m_bufferStart + this->m_bufferPos;
	this->flushBuffer();
    this->m_bufferPos = 0;
}


void IndexOutput::seek(int64_t pos)
{
	flush();
    m_bufferStart = pos;
    fseek( fp, pos, SEEK_SET );
}


void IndexOutput::flushBuffer()
{
    fwrite( m_buffer, m_bufferPos, 1, fp );
}
