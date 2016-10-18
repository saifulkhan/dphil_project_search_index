#ifndef TREEMAPE_H
#define TREEMAPE_H

#include <string>
#include <iostream>
#include <json_spirit_writer.h>
#include <json_spirit_value.h>

#include "CacheParser.h"
#include "Layout.h"
#include "NodeTM.h"

#define DEFAULT_DEPTH 4

using namespace std;

class Treemap {
private:
    int          m_x;
    int          m_y;
    int          m_width;
    int          m_height;
    NodeTM*      m_rootNodeTM;
    Layout       m_layout;
    CacheParser* m_cacheParser;

    map<string, RectF> m_coordinate;

    json_spirit::Object toJSONObject(NodeTM* node);
    void printKDistant(NodeTM *root , int k, json_spirit::Array& output);
    string layout();

    json_spirit::Array toJSONArray(NodeTM* node); // Not Used
public:
    Treemap();
    ~Treemap();

    string buildTreemap(const int x, const int y, const int height, const int width);
    string zoomTreemap(const string path);
    string changeTreemapDepth(const int depth); // Not Used

    RectF coordinate(const string& fileName);
};

#endif // TREEMAPE_H
