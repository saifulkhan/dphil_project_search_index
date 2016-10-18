#ifndef NODETM_H
#define NODETM_H

#include <iostream>
#include <vector>

#include <FileInfo.h>

using namespace std;


/*****************************************************************************************************************************
 * Rectangle (custom implementation)
 ******************************************************************************************************************************/

class RectF
{
private:
    double m_x;
    double m_y;
    double m_width;
    double m_height;

public:
    RectF(double x = 0.0, double y = 0.0, double width = 0.0, double height = 0.0);
    void setX(double x);
    void setY(double y);
    void setHeight(double height);
    void setWidth(double width);
    void adjust(double dx, double dy, double dwidth, double dheight);
    double x() const;
    double y() const;
    double width() const;
    double height() const;
    pair<double, double> center() const;
    string rect() const;

    friend ostream& operator<<(ostream& os, const RectF& rectF);
};


/*****************************************************************************************************************************
 * The Node tree of the treemap is stored in this DS
 ******************************************************************************************************************************/

struct NodeTM
{
public:
    FileInfo         fileInfo;
    int              depth;
    int64_t          value;
    RectF            rectF;
    vector <NodeTM*> children;


    NodeTM(FileInfo fileInfo, int depth, int64_t value );
    ~NodeTM();
    void deleteAll(NodeTM* nodeTM);
    void print( NodeTM *item );
};

bool TreemapLessThan (const NodeTM *a, const NodeTM *b);

#endif // NODETM_H
