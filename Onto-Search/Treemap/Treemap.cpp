#include "Treemap.h"


Treemap::Treemap() {
    m_rootNodeTM = NULL;
    m_cacheParser = new CacheParser();
}


Treemap::~Treemap()
{
    // m_rootNodeTM->deleteAll(m_rootNodeTM); // deleted from cacheparser
    delete m_cacheParser;
}


/*********************************************************************************************************
 *  1. The tree is created from Cache or Existing file system(by scaning it).
 *  2. Layout is done here first
 *  3. The nodes upto depth 3 (0, 1, 2) is returned at first instance.
 *  4. Relayout if x, y, width, height changed
 * Ideally NodeTM structure is returned by the CacheParesr. this is always same; only lay out changes.
 *********************************************************************************************************/

string Treemap::buildTreemap(const int x, const int y, const int width, const int height) {

    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;

    // parse cache
    m_rootNodeTM = m_cacheParser->buildTree();
    return this->layout();
}


string Treemap::zoomTreemap(const string path) {

    cout << __PRETTY_FUNCTION__ << "path = " << path << endl;

    // parse cache
    m_rootNodeTM = m_cacheParser->buildTree(path);
    return this->layout();
}


string Treemap::layout() {

    //m_rootNodeTM->print(m_rootNodeTM);

    /*
     * When scale, height, width etc changed by control window only new layout will be done,
     * whre the NodeTM.rectF will only change
     */
    m_layout.doLayout(m_rootNodeTM, RectF(m_x, m_y, m_width, m_height));
    m_coordinate.clear();
    //cout << __PRETTY_FUNCTION__ << "m_coordinate.size()=" << m_coordinate.size() << endl;
    m_coordinate = m_layout.coordinate();
    //cout << __PRETTY_FUNCTION__ << "m_coordinate.size()=" << m_coordinate.size() << endl;


    #ifdef DBG_TREEMAP
    m_rootNodeTM->print(m_rootNodeTM);
    #endif

    json_spirit::Array output;

    for (unsigned i = 0; i <= DEFAULT_DEPTH; ++i) {
        this->printKDistant(m_rootNodeTM, i, output);
        //cout << __PRETTY_FUNCTION__ << "Depth: " << i << endl;
        //cout << (json_spirit::write(output, json_spirit::pretty_print)) << endl;
    }


    /*
     * Convert the whole tree to JSON
     */
    //json_spirit::Object root_json = this->toJSONObject(m_rootNodeTM);

    /*
     *  DBG: Write to file, can be used for debugging
     *  or, use when developing w/o angular.
     */
    ofstream os;
    os.open("treemap.json");
    json_spirit::write(output, os, json_spirit::pretty_print);
    os.close();

    string jsonstr =  json_spirit::write(output);
    return jsonstr;
}




// Not Used
string Treemap::changeTreemapDepth(const int depth)
{
    if (depth < 3)
        return "";
    json_spirit::Array output;
    this->printKDistant(m_rootNodeTM, depth, output);
    cout << __PRETTY_FUNCTION__ << "Depth: "  << depth << endl;

    //cout << (json_spirit::write(output, json_spirit::pretty_print)) << endl;
    string jsonstr =  json_spirit::write(output);
    return jsonstr;
}


/*********************************************************************************************************
 *  Convert the NodeTM tree to a array(each layer/depth) of JSON nodes
 *********************************************************************************************************/

void Treemap::printKDistant(NodeTM *root , int k, json_spirit::Array& output) {
   if(root == NULL)
      return;

   if (k == 0) {
       json_spirit::Object ch;
       ch.push_back(json_spirit::Pair("name", root->fileInfo.m_fileName));
       ch.push_back(json_spirit::Pair("path", root->fileInfo.m_path));
       ch.push_back(json_spirit::Pair("type", root->fileInfo.m_type));
       ch.push_back(json_spirit::Pair("depth",root->depth));
       ch.push_back(json_spirit::Pair("x",    root->rectF.x()));
       ch.push_back(json_spirit::Pair("y",    root->rectF.y()));
       ch.push_back(json_spirit::Pair("w",    root->rectF.width()));
       ch.push_back(json_spirit::Pair("h",    root->rectF.height()));
       output.push_back(ch);

       return ;
   } else {
       for(vector <NodeTM*>::iterator it = root->children.begin(); it != root->children.end(); ++it) {
           printKDistant(*it, k - 1, output) ;
       }
   }
}



/*********************************************************************************************************
 *  Other Functions
 *********************************************************************************************************/

RectF Treemap::coordinate(const string& fileFullPath) {
    RectF rect = m_coordinate[fileFullPath];

    #ifdef DBG_TREEMAP
    if (rect.x() == 0 || rect.y() == 0)
        cout << __PRETTY_FUNCTION__ << fileFullPath << ": Not-found in map: " << rect << endl;
    else
        cout << __PRETTY_FUNCTION__ << fileFullPath << ": Found in the map: " << rect << endl;
    #endif

    return rect;
}


/*********************************************************************************************************
 * Not Used
 * Convert the NodeTM tree to a JSON tree
 *********************************************************************************************************/

json_spirit::Object Treemap::toJSONObject(NodeTM* node)
{
    json_spirit::Object parent;
    parent.push_back(json_spirit::Pair("name",  node->fileInfo.m_fileName));
    parent.push_back(json_spirit::Pair("type",  node->fileInfo.m_type));
    parent.push_back(json_spirit::Pair("x",     node->rectF.x()));
    parent.push_back(json_spirit::Pair("y",     node->rectF.y()));
    parent.push_back(json_spirit::Pair("w", node->rectF.width()));
    parent.push_back(json_spirit::Pair("h",node->rectF.height()));

    if (node->children.size() > 0 && node->depth < atoi(JSON_TREEMAP_DEPTH))
    {
        json_spirit::Array children_array;

        for(vector <NodeTM*>::iterator it = node->children.begin(); it != node->children.end(); ++it)
        {
            // If, it is a leaf node, just add it to the array.
            // Else, recurse it first & then add to the array.
            if ((*it)->children.size() <= 0)
            {
                json_spirit::Object leaf;
                leaf.push_back(json_spirit::Pair("name", (*it)->fileInfo.m_fileName));
                leaf.push_back(json_spirit::Pair("type", (*it)->fileInfo.m_type));
                leaf.push_back(json_spirit::Pair("x",     (*it)->rectF.x()));
                leaf.push_back(json_spirit::Pair("y",     (*it)->rectF.y()));
                leaf.push_back(json_spirit::Pair("w", (*it)->rectF.width()));
                leaf.push_back(json_spirit::Pair("h",(*it)->rectF.height()));


                children_array.push_back(leaf);
            }
            else
            {
                json_spirit::Object nonLeaf = toJSONObject(*it);
                children_array.push_back(nonLeaf);
            }
        }
        parent.push_back(json_spirit::Pair("children", children_array));
    }

    return parent;
}
