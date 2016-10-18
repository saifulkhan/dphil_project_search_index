#ifndef STDHEADER_H_
#define STDHEADER_H_

#include <sys/types.h>
#include <wchar.h>
#include <queue>
#include <vector>
#include  <stdio.h>  
#include <stdint.h>

    typedef unsigned char	byte;
	
    #define   STORE_VINT 1
	#define   STORE_INT 2 
	#define   STORE_LONG 3
	#define   STORE_VLONG 4
	#define   STORE_STRING 5
	
	#define   STORE_YES 1
	#define   STORE_NO 2
	
    #define   STORE_NO_TOKEN 1
	#define   STORE_TOKEN 2
	#define   STORE_KEYWORD 3
	
    #define   SEGSTATUS_WRITE 1
    #define   SEGSTATUS_CLOSE 2 

#endif /*STDHEADER_H_*/
