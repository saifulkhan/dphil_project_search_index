#ifndef TREEMAPE_H
#define TREEMAPE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDesktopWidget> // Dont know about this header file. Added to avoid Qt5 compilation error.
#include <QApplication>
#include <QSettings>
#include <QFileDialog>
#include <QFileInfo>

#include <string>

#include <CacheParser.h>
#include <NodeTM.h>
#include <Layout.h>

#include "Tile.h"
#include "ui_Treemap.h"

class Treemap : public QDialog
{
    Q_OBJECT
private:
    Ui::Treemap*    ui;
    // Settings
    QSettings*      settings;
    QString         m_rootDir;
    QString         lastRootDir;      // TODO
    int             maxdepth;
    int             minscale;
    int             width;
    int             height;

    NodeTM*         m_rootNodeTM;
    Layout          m_layout;
    CacheParser*    m_cacheParser;
    QGraphicsScene* scene;
    Tile*           m_rootTile;
    map<string, RectF> m_coordinate;

    void loadSettings();
    void saveSettings();

private:
    // Singleton
    static Treemap* m_treemap;
    Treemap(QGraphicsScene *scene);
    Treemap(Treemap const&) { }
    Treemap& operator=(Treemap const&) { }

    void scanFileSystem();
    void scanFileSystem (QDir, NodeTM*);

    void createTiles(NodeTM* parentItem);
    bool filterItem(NodeTM* item);

public:
    static Treemap* instance(QGraphicsScene *scene);
    ~Treemap();
    void buildTreemap();
    RectF coordinate(const string& fileName);
    Tile* getRootTile() const { return m_rootTile; }

signals:
    void signal_Treemap(bool);

private slots:
    void on_browseButton_clicked();
    void on_applyButton_clicked();

};


#endif // TREEMAPE_H
