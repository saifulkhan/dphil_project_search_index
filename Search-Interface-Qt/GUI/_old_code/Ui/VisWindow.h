#ifndef VISWINDOW_H
#define VISWINDOW_H

#include "ui_VisWindowForm.h"
#include <QtGui>
#include <QFileDialog>
#include <vector>
#include <QPair>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string.h>

#include "SecondaryDialog.h"
#include "PrimaryDialog.h"
#include "Data/Data.h"
#include "Data/TableModel.h"
#include "Data/OpenSave.h"
#include "Data/SearchResult.h"
#include "Mapping/VisualMapping.h"
#include "GlobalVariables.h"
#include "Treemap/TreemapInterface.h"
#include "Search/SearchInterface.h"
#include "Search/Find.h"
#include "Crawler/Crawler.h"

class Secondary;
class Animation;
class Glyph;
class PrimaryGlyph;
class SecondaryGlyph;

using namespace std;

class VisWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::VisWindowForm *ui;
    // View and scene
    QGraphicsScene *_scene;
    //QGraphicsView *_view;

    /// Data
    Data *_data;
    QList <File_S> _fileList;

    /// Search and crawler Interface
    Crawler *crawler;
    Buffer *_buffer;
    //FindNS::Find *_query;
    SearchResult *_searchResult;


    /// The treemap image path
    TreemapNS::TreemapInterface *treemap;
    TreemapNS::TreemapItem *rootTreemapItem;

    /// Property Windows
    PrimaryDialog *_priDialog;
    SecondaryDialog *_secDialog;
    VisualMapping *_visualMappingDialog;

    /// Property vector. primary (generally static), secondary (has static, animation, TF) properties.
    vector <PrimaryProperty_S> _priProperty;
    vector <Secondary> _secProperty;
    vector <Animation> _secAnProperty;

    /// store the crreated glyphs
    vector <Glyph *> _priGlyphVec;
    vector <Glyph *> _secGlyphVec;


    ///

    void _createToolbar();
    void _createSceneView ();

    /// Generic
    Glyph* _createGlyph (PrimaryProperty_S);
    Glyph* _createGlyph (Secondary, Animation);
    void _createPriGlyphs ();
    void _createSecGlyphs ();
    void  _addtoScene (vector <Glyph *> &);    // Takes a vector of glyphs and add the glyphs to scene.
    void _deleteGlyphs (vector <Glyph *> &);   // Remove glyphs from scene and clear the vector.
    void _redrawGlyphs ();

    /// Show/Hide
    void _showGlyph (bool, vector <Glyph *> &);
    /// Animation Generic
    void _animate (bool, vector <Glyph *> &);

    // Open the treemap image if there
    void _openTreemap (QString) const;

    // Data and Mapping
    void _openData ();
    void _mapProperties ();

private slots:
    void on_openTreemap_triggered();
    void on_openData_triggered();
    void on_actionExit_triggered();
    void on_openPriProperty_triggered();
    void on_openSecProperty_triggered();
    void on_openVisualMapping_triggered();
    void on_saveView_triggered();
    void on_openView_triggered();

    void on_searchButton_clicked();

    // Received signals
    void PrimaryDialog_Slot (PrimaryProperty_S);
    void SecondaryDialog_Slot (Secondary, Animation);
    void VisualMapping_Slot ();

    void on_treemapSetting_triggered();
    void on_crawlerSetting_triggered();
    void on_actionIndexBrowser_triggered();
    void on_actionSqlitesStudio_triggered();

public:
    VisWindow (QWidget *parent = 0);
    ~VisWindow();
};

#endif // VISWINDOW_H
