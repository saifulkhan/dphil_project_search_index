
#include "NodeTM.h"


/*****************************************************************************************************************************
 * The Node tree of the treemap is stored in this DS
 ******************************************************************************************************************************/

bool TreemapLessThan (const NodeTM *a, const NodeTM *b)
{
    return (a->value) > (b->value);
}


NodeTM::NodeTM (FileInfo fileInfo, int depth, int64_t value)
{
    this->fileInfo  = fileInfo;
    this->depth     = depth;
    this->value     = value;
    this->children.clear();
}


NodeTM::~NodeTM()
{

}

void NodeTM::deleteAll(NodeTM* node)
{
    #ifdef DBG_TREEMAP
    cout << node->fileInfo.m_fileName << ", " << node->children.size() << endl;
    #endif

    NodeTM* children;
    for (vector<NodeTM*>::iterator it = node->children.begin(); it != node->children.end(); ++it)
    {
        children = *it;
        //node->children.erase(it);
        this->deleteAll(children);
    }
    #ifdef DBG_TREEMAP
    cout << "Del: " << node->fileInfo.m_fileName << ", " << node->children.size() << endl;
    #endif

    delete node;
}


/*
 * Prints the Treemap structure, item and its sub-items
 */

void NodeTM::print(NodeTM *node)
{
    /*
     * Directory else, file
     */
    if (node->fileInfo.m_path.empty())
    {
        cout << node->fileInfo.m_fileName << ", " ;

    }
    else
    {
       cout << node->fileInfo.m_path << "/" << node->fileInfo.m_fileName << ", ";
    }

    cout << node->depth << ", " << (node->value) << ", " << node->rectF << endl;

    for (vector<NodeTM*>::iterator it = node->children.begin(); it != node->children.end(); ++it)
    {
        if ( (*it)->children.size() == 0 )
        {
            cout << (*it)->fileInfo.m_docId << " : "<< (*it)->fileInfo.m_path << "/" << (*it)->fileInfo.m_fileName << ", " <<
                    (*it)->depth << ", " <<
                    convertSizeUnit((*it)->value) << ", " <<
                    (*it)->rectF << endl;
        }
        else
            print(*it);
    }
}


/*****************************************************************************************************************************
 * Rectangle (custom implementation)
 ******************************************************************************************************************************/

RectF::RectF(double x, double y, double width, double height)
{
    m_x      = x;
    m_y      = y;
    m_width  = width;
    m_height = height;
}

void RectF::setX(double x)
{
    m_x = x;
}

void RectF::setY(double y)
{
    m_y = y;
}

void RectF::setHeight(double height)
{
    m_height = height;
}

void RectF::setWidth(double width)
{
    m_width = width;
}

void RectF::adjust(double dx, double dy, double dwidth, double dheight)
{
    m_x     = m_x + dx;
    m_y     = m_y + dy;
    m_width = m_width + dwidth;
    m_height= m_height + dheight;
}

double RectF::x() const
{
    return m_x;
}

double RectF::y() const
{
    return m_y;
}

double RectF::width() const
{
    return m_width;
}

double RectF::height() const
{
    return m_height;
}

pair<double, double> RectF::center() const
{
    return pair<double, double>((m_x + m_width / 2), (m_y + m_height / 2));
}

string RectF::rect() const
{
    std::stringstream jsonformat;
    jsonformat << "{x: " << this->x() << ", y: " << this->y() << ", width: " << this->width() << ", height: " << this->height() << "}";
    return jsonformat.str();
}

ostream& operator<<(ostream& os, const RectF& rectF)
{
    os << "(" << rectF.x() << ", " << rectF.y() << ")" << " " << rectF.width() << "X" << rectF.height();
    return os;
}
