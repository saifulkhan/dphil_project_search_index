#include "Layout.h"


/*****************************************************************************************************************************
 * Squarify
 ******************************************************************************************************************************/

void Squarify::doSquarify(NodeTM *rootNodeTM, RectF rootRectF)
{
    sort(rootNodeTM->children.begin(), rootNodeTM->children.end(), TreemapLessThan);
    _doSquarify(rootNodeTM->children, 0, rootNodeTM->children.size() - 1, rootRectF);
}


/**
 * Use the squarified algorithm outlined by Mark Bruls, Kees Huizing, and Jarke J. van Wijk
 * "http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.36.6685&rep=rep1&type=pdf"
 *
 * we use the well-known squarify layout to maintain aspect ratios as near as possible  to a square.
 * It in turn uses the original slice layout to split rows or columns we do ourselves and then our children
 * and do it recursively, despite the fact that the Treemap is currently on 2 deep that may change in the future
 *
 * This iterates over sections of the list and calls itself to process mid/left sections
 * Check the below links -
 * http://www.codeproject.com/Articles/7039/Squarified-Treemaps-in-XAML-C-using-Microsoft-Long
 * http://jectbd.com/?p=271
 **/

void Squarify::_doSquarify(vector<NodeTM*> items, int start, int end, RectF bounds)
{
    if (start > end)
        return;
    if (end - start < 2) // Only slice.
    {
        slice( items, start, end, bounds );
        return;
    }

    double x = bounds.x(),
           y = bounds.y(),
           w = bounds.width(),
           h = bounds.height();

    double total = 0;
    for ( int i = start; i <= end; i++ )
        total += items[i]->value;

    int mid = start;
    double a = items[start]->value / total;
    double b = a;

    if (w < h)
    {
        while (mid <= end)
        {
            double aspect = normAspect (h, w, a, b);
            double q = items[mid]->value / total;
            if (normAspect(h, w, a, b + q) > aspect)
                break;
            mid ++;
            b = b + q;
        }
        slice( items, start, mid, RectF (x, y, w, h*b) );
        _doSquarify(items, mid + 1, end, RectF(x, y + h*b, w, h*(1 - b) ));
    }
    else
    {
        while (mid <= end)
        {
            double aspect = normAspect (w, h, a, b);
            double q = items[mid]->value / total;
            if ( normAspect(w,h,a,b+q) > aspect )
                break;
            mid ++;
            b = b + q;
        }
        slice( items, start, mid, RectF( x, y, w * b, h ) );
        _doSquarify( items, mid+1, end, RectF( x + w * b, y, w * (1 - b), h ) );
    } // if-else

}


/**
 * Slice the bound rectangle into strips (start - end), either horizontally or vertically (whichever has the longest side)
 **/
void Squarify::slice(vector<NodeTM*> items, int start, int end, RectF bounds )
{
    // setup
    double total=0, accumulator=0; // total value of items and running total
    for (unsigned int i = start; i <= (unsigned)end && i < items.size(); i++)
        total += items[i]->value;

    // slice em up!
    for (unsigned int i = start; i <= (unsigned)end && i < items.size(); i++)
    {
        double factor = items[i]->value / total;
        if (bounds.height() >= bounds.width())
        {
            // slice em into a vertical stack
            items[i]->rectF.setX (bounds.x());
            items[i]->rectF.setWidth (bounds.width());
            items[i]->rectF.setY (bounds.y() + bounds.height() * (1 - accumulator - factor) );
            items[i]->rectF.setHeight (bounds.height() * factor);
        }
        else
        {
            // slice em into a horizontal stack
            items[i]->rectF.setX (bounds.x() + bounds.width() * (1 - accumulator - factor));
            items[i]->rectF.setWidth (bounds.width() * factor);
            items[i]->rectF.setY (bounds.y());
            items[i]->rectF.setHeight (bounds.height());
        }
        accumulator += factor;
    }
}


double Squarify::normAspect(double bigger, double smaller, double a, double b)
{
    double x = (bigger * b) / (smaller * a / b);
    if (x < 1)
        return 1 / x;
    return x;

}

/*****************************************************************************************************************************
 * Layout
 ******************************************************************************************************************************/

void Layout::doLayout(NodeTM* rootNodeTM, RectF rootRectF)
{
    rootNodeTM->rectF = rootRectF;
    this->_doLayout(rootNodeTM, rootRectF);
    this->coordinateMap(rootNodeTM);

}

void Layout::_doLayout(NodeTM* nodeTM, RectF rectF)
{
    double borderWidth = atoi(BORDER_WIDTH);

    if (rectF.height() - borderWidth > 0 && rectF.width() - borderWidth > 0)
    {
        rectF.adjust(borderWidth, borderWidth, -(2 * borderWidth), -(2 * borderWidth));
    }
    m_squarify.doSquarify(nodeTM, rectF);

    for (vector<NodeTM*>::iterator it = nodeTM->children.begin(); it != nodeTM->children.end(); ++it)
        this->_doLayout((*it), (*it)->rectF);
}




/*
 * Craete the hash table of "coordinate", after layout is done.
 */

void Layout::coordinateMap(NodeTM* node)
{
    vector<NodeTM*>::iterator it;

    for (it = node->children.begin(); it != node->children.end(); ++it)
    {
        if ((*it)->fileInfo.m_type.compare("") != 0)    // Skip directories
        {
            string fileFullPath        = (*it)->fileInfo.m_path + "/" + (*it)->fileInfo.m_fileName;
            m_coordinate[fileFullPath] = (*it)->rectF;
            #ifdef DBG_TREEMAP
            cout << __PRETTY_FUNCTION__ << fileFullPath << ": " << m_coordinate[fileFullPath] << endl;
            #endif
        }
    }

    /*
     * Iterate and recurse directory.
     */
    for (it = node->children.begin(); it != node->children.end(); ++it)
    {
        if ((*it)->children.size() > 0)
            this->coordinateMap(*it);
    }
}
