#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <set>
#include "FileInfo.h"

using namespace std;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ STRING tokenise ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

queue<string> tokenise(const string &str, const string &delimiter);
vector<string> tokeniseStrToVector(const string &input, const string &delimiter);

#endif
