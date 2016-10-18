#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QApplication>
#include <QDesktopWidget>
#include <QThread>
#include <QFileInfo>
#include <QGraphicsScene>

#include "Search/Buffer.h"
#include "Treemap/TreemapItem.h"
#include "Glyph/PrimaryGlyph.h"

class SearchResult : public QThread
{
    Q_OBJECT

private:
    Buffer *buffer;
    QVector <QFileInfo> fileInfoVec;        // search results
    TreemapNS::TreemapItem *rootTreemapItem;
    QGraphicsScene *scene;
    QRectF getAxis( const QFileInfo& );

public:
    explicit SearchResult (QGraphicsScene*, QVector <QFileInfo>  fileInfoVec, Buffer*, QObject *parent = 0);
    void run();

signals:

public slots:

};

#endif // SEARCHRESULT_H
