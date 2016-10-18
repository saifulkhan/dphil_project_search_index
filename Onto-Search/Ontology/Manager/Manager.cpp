#include "OntologyFactory.h"

// Prototypes
void createOntology(string);
void testPrint(Ontology* ontology);
void testUpdate();

// Main
int main(int argc, char *argv[])
{


    //createOntology(string("TermOntology"));
    //createOntology(string("TypeOntology"));
    //createOntology(string("SizeOntology"));


    // Test
    //testUpdate();
    Ontology* ontology = OntologyFactory::createConnection("TermOntology");
    testPrint(ontology);
    return EXIT_SUCCESS;
}

// Functions
void createOntology(string name)
{
    Ontology* ontology = OntologyFactory::createConnection(name);
    ontology->createOntology();

    testPrint(ontology);
    delete ontology;     // close
}

void testPrint(Ontology* ontology)
{
    cout <<__PRETTY_FUNCTION__ << endl;
    ontology->findNeighbors("draft");
    ontology->findNeighbors("budget");
    ontology->findNeighbors("building");
}

void testUpdate()
{
    cout <<__PRETTY_FUNCTION__ << endl;

    Ontology *ontology = NULL;
    map <string, double> tempmap;

    ontology = OntologyFactory::createConnection(string("TermOntology"));
    ontology->findNeighbors("draft");
    tempmap["draught"] = 0.1234;
    tempmap["blueprint"] = 0.789;

    ontology->updateNeighbors("draft", tempmap);
    delete ontology;

    // Type
    ontology = OntologyFactory::createConnection(string("TypeOntology"));
    ontology->findNeighbors("draft");
    tempmap["Developer"] = 0.123;
    tempmap["Web"] = 0.789;
    ontology->updateNeighbors("draft", tempmap);
    delete ontology;


    // Type
    ontology = OntologyFactory::createConnection(string("SizeOntology"));
    ontology->findNeighbors("draft");
    tempmap["B"] = 0.123;
    tempmap["GB"] = 0.789;
    ontology->updateNeighbors("draft", tempmap);
    delete ontology;
}
