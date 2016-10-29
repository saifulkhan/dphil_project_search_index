#ifndef ONTOLOGYFACTORY_H
#define ONTOLOGYFACTORY_H

#include <iostream>
#include <cassert>
#include "Ontology.h"
#include "TermOntology.h"
#include "TypeOntology.h"
#include "SizeOntology.h"

using namespace std;

class OntologyFactory
{
    string ontologyType;

public:
    static Ontology* createConnection(string type);
};

#endif // ONTOLOGYFACTORY_H
