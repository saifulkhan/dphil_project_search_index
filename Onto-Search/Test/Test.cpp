#include <iostream>
#include <string>
#include "../QueryProcessor.h"
#include "../QueryParser.h"

using namespace std;

void test_treemap();
void test_click();
void test_queryParser();
void test_queryProcessor();

string query1 = "{\"key\":\"draft apple\",\"type\":\"docx pdf xlsx\",\"sizefrom\":\"20 B\",\"sizeto\":\"30 KB\",\"datefrom\":\"\",\"dateto\":\"\"}";
string query2 = "{\"key\":\"building\"\",\"type\":\"docx pdf xlsx\",\"sizefrom\":\"\",\"sizeto\":\"\",\"datefrom\":\"\",\"dateto\":\"\"}";
string query3 = "{\"key\":\"draft\",\"type\":\"docx pdf\",\"sizefrom\":\"\",\"sizeto\":\"\",\"datefrom\":\"\",\"dateto\":\"\"}";


int main(int argc, char *argv[])
{

    //test_treemap();
    //test_queryParser();
    test_queryProcessor();


    return EXIT_SUCCESS;
}


void test_queryParser()
{
    cout << __PRETTY_FUNCTION__ << endl;
    QueryParser parser;
    Query queryObj = parser.parse(query1);
    queryObj.print();

    queryObj = parser.parse(query2);
    queryObj.print();

    queryObj = parser.parse(query3);
    queryObj.print();
}

void test_queryProcessor() {
    vector <FileInfoX>::iterator itF;
    QueryProcessor qp;

    cout << __PRETTY_FUNCTION__ << " Test searching, query: " << query3 << endl;
    string result = qp.search(query3);

    //for (itF = result.begin(); itF != result.end(); ++itF)
    //cout << result << endl;

    cout << __PRETTY_FUNCTION__ << " Test searching, query: " << query2 << endl;
    qp.search(query2);
}


void test_treemap()
{
    cout << __PRETTY_FUNCTION__ << endl;

    // TODO: should test treemap without QP.

    QueryProcessor qp;

    // build & 2 depth
    cout << qp.buildTreemap(10, 10, 800, 400) << endl;
    // depth
    cout << qp.changeTreemapDepth(2) << endl;
    cout << qp.changeTreemapDepth(3) << endl;
    cout << qp.changeTreemapDepth(4) << endl;

    string result = qp.search(query3);
    cout << result << endl;
}




// Neural Net test
#if 0
#include "NeuralNet.h"

int main()
{
    NeuralNet *net = new NeuralNet;

    double w = 0.5;


    for (unsigned i = 0; i < 1000; ++i)
    {
        w = net->train(w, true);
        cout << w << endl;
    }


/*
    double x = 1.0;
    double y;
    double e;
    double z = 1.0; // 1 or 0
    double delta;
    double eta = 0.4;

    for (unsigned i = 0; i < 10000000; ++i)
    {
        e = x * w;
        y = Neuron::transferFunction(e);
        delta = z - y;

        cout << "y = " << y << " | delta = " << delta << endl;
        cout << "w = " << w << " | " ;

        w = w + (eta * delta * Neuron::transferFunctionDerivative(e) * x);

        cout << "w' = " << w << endl;
        //cout << "Normalised w = " << Neuron::transferFunction(w) << endl;

    }

*/
    return 0;
}
#endif

