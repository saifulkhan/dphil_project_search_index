// http://pravinchavan.wordpress.com/2013/11/08/c-binding-with-node-js/

#include <string>
#include <sstream>

class myclass {
   int myx;

  public:

    myclass() { myx=0; }
    void setx(int newx);
    int  getx();
    int square(int x);
    std::string jsonString(int val);
    std::string concatresult(int,std::string);
};
