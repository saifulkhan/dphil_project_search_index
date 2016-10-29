#ifndef LAYOUT_H
#define LAYOUT_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>

#include <FileInfo.h>

#include "NodeTM.h"

using namespace std;

/*****************************************************************************************************************************
 * Squarify
 ******************************************************************************************************************************/

class Squarify
{
private:
    // Key squarification functions
    void _doSquarify(vector<NodeTM*> items, int start, int end, RectF bounds);
    void slice(vector<NodeTM*>, int, int, RectF);
    double normAspect(double bigqer, double smaller, double a, double b);

public:
    Squarify() {}
    void doSquarify(NodeTM *rootNodeTM, RectF rootRectF);
};


/*****************************************************************************************************************************
 * Layout
 ******************************************************************************************************************************/

class Layout
{
private:
    Squarify            m_squarify;
    map<string, RectF>  m_coordinate;

private:
    void _doLayout(NodeTM* nodeTM, RectF rectF);
    void coordinateMap(NodeTM* item);

public:
    Layout() {}
    void doLayout(NodeTM* nodeTM, RectF rectF);
    map<string, RectF> coordinate() const { return m_coordinate; }
};

#endif
