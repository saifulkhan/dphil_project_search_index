#ifndef CONVERSION_H
#define CONVERSION_H


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <math.h>
#include <inttypes.h>
#include <regex>

#include "Algorithm.h"

using namespace std;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STRING-NO conversion ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

string int64ToString(const  std::int64_t& no);                                 // usage: numberToString(number)
std::int64_t stringToInt64(const string &str);
double stringToDouble(const string &str);
wstring stringToWString(const string &s);
string wstringToString(const wstring &ws);
string stringToLower(const string &str);


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ NUMBER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// calculate size : convert bytes to TB, GB, etc.
#define DIM(x) ( sizeof(x) / sizeof(*(x)) )
char* convertSizeUnit(uint64_t size);
uint64_t unitToSize(const string sizeStr);

double normalizeScale( double originalScale, double newScale, double originalValue );
double normalize( double originalStart, double originalEnd, double newStart, double newEnd, double originalValue);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OTHER ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setBit(int &number, const unsigned &bit);
bool getBitVal(const int &number, const unsigned &bit);

#endif
