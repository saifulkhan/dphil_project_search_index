/*
 * Input from a file / file read
 */

#ifndef INDEXINPUT_H_
#define INDEXINPUT_H_

#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "stdHeader.h"

using namespace std;

class IndexInput
{	
protected:
    char *m_buffer;
    int	  m_buffersize;
    long  m_bufferStart;
    int	  m_bufferPos;
    FILE  *m_fp;
    char  *m_fileName;

public:
	IndexInput();
    IndexInput( char *file );
    virtual ~IndexInput();
    void open( char *m_file );
    void close();

	byte  readByte();
	int32_t readInt();
	int32_t readVint();
    std::int64_t readLong();
    std::int64_t readVlong();
    void  readChars( char *buffer, std::int64_t start, std::int64_t len );
    void  readString( string &str );
    void  seek( std::int64_t pos );
    std::int64_t getFilePointer();
};

#endif /*INDEXINPUT_H_*/
