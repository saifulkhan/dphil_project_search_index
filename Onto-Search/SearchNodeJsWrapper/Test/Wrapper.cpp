#include "Wrapper.h"
#include <stdio.h>
#include <string>
void myclass::setx(int newx) { myx = newx; }
int  myclass::getx() { return myx; }
int myclass::square(int x) { return x * x; }

std::string myclass::jsonString(int val)
{
    std::string json = "[\"test\", \"test2\"]";
    return json;
}

std::string myclass::concatresult(int inputval,std::string inputstr)
{
    std::stringstream ss;
    ss << inputstr << inputval;
    return ss.str();
}


