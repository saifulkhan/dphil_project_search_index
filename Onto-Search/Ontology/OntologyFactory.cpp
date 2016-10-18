#include "OntologyFactory.h"

Ontology* OntologyFactory::createConnection(string type)
{
    wstring cfgFile = stringToWString(GDB_CFG);

    if (type.compare("TermOntology") == 0)
    {
        return new TermOntology(cfgFile, stringToWString(TERM_ONTOLOGY), L"TermOntology");
    }
    else if (type.compare("TypeOntology") == 0)
    {
        return new TypeOntology(cfgFile, stringToWString(TYPE_ONTOLOGY), L"TypeOntology");
    }
    else if (type.compare("SizeOntology") == 0)
    {
         return new SizeOntology(cfgFile, stringToWString(SIZE_ONTOLOGY), L"SizeOntology");
    }
    else if (type.compare("DateOntology") == 0)
    {

    }
    else
    {
        throw "Invalid Ontology type:  OntologyFactory::createConnection().";
    }
}
