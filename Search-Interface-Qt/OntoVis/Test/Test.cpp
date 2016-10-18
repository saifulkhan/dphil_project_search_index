#include <QApplication>
#include <QtCore>

#include "GraphWidget.h"
#include <OntologyFactory.h>

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

     GraphWidget *widget = new GraphWidget;
     widget->show();



     Ontology*       m_termOntology, *m_typeOntology, *m_sizeOntology;
     m_termOntology = OntologyFactory::createConnection("TermOntology");
     m_typeOntology = OntologyFactory::createConnection("TypeOntology");
     m_sizeOntology = OntologyFactory::createConnection("SizeOntology");

     map<string, double> m_termWeightMap;
     map<string, double> m_typeWeightMap;
     map<string, double> m_sizeWeightmap;

     string m_term = "draft";

     m_termWeightMap = m_termOntology->findNeighbors(m_term);
     m_typeWeightMap = m_typeOntology->findNeighbors(m_term);
     m_sizeWeightmap = m_sizeOntology->findNeighbors(m_term);

    widget->addItems(m_term, m_termWeightMap);


/*
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::darkGray);
    GraphWidget *widget1 = new GraphWidget(scene);
    widget1->show();
    widget1->showMaximized();

    Node* node = new Node(widget1);
    scene->addItem(node);
*/


    return app.exec();
}
