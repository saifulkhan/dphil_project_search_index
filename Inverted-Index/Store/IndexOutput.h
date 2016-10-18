#ifndef INDEXOUTPUT_H_
#define INDEXOUTPUT_H_

#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <assert.h>
#include "stdHeader.h"

using namespace std;

class IndexOutput
{

private:
    char * m_fileName;

protected:
    char    *m_buffer;
    int		m_buffersize;
    long    m_bufferStart;		// m_buffer
    int     m_bufferPos;        // m_buffer
    FILE    *fp;
    bool    isClose;

public:
	IndexOutput();
    IndexOutput(char * m_file, bool create);
    virtual ~IndexOutput();

    void  writeInt( int32_t  value);
	void  writeVint( int32_t  value);
	void  writeByte(byte  b);
    void  writeString( string  &str);
    void  writeLong(std::int64_t value);
    void  writeVlong(std::int64_t value);
    void  writeChars(const char * s ,std::int64_t start, std::int64_t len);
    std::int64_t getFilePointer();
	void close();
    void flush();
    void flushBuffer() ;
    void seek(std::int64_t pos);
};

#endif /*INDEXOUTPUT_H_*/
