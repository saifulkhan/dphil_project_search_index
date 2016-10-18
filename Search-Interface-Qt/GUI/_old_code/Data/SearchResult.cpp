#include "SearchResult.h"

SearchResult::SearchResult (QGraphicsScene *_scene, QVector <QFileInfo> _fileInfoVec, Buffer *_buffer, QObject *parent) :
    scene (_scene), fileInfoVec(_fileInfoVec), buffer (_buffer), QThread(parent)
{

}

void SearchResult::run()
{
    QFileInfo fileInfo;
    for (int i = 0; i <  fileInfoVec.size(); i++) {

        qDebug() << __PRETTY_FUNCTION__ << fileInfo.filePath();
        //buffer->read(&fileInfo);
    }

    qDebug() << __PRETTY_FUNCTION__ << " Complete.";

}


QRectF SearchResult::getAxis(const QFileInfo &fileInfo)
{
   /* void TreemapItem::print( TreemapItem *item )
    {
        qDebug() << "Dir:" << item->fileInfo.filePath() << "," << item->depth << ", " << (double) item->value / (1024 * 1024) << "MB, " << item->rectF;

        foreach ( TreemapItem *it, item->children ) {
            if ( it->children.size() == 0 )
                qDebug() << "File: " << it->fileInfo.filePath() << ", " << it->depth << ", " << (double) it->value / (1024 * 1024) << "MB, " << it->rectF;
            else
                print( it );
        }
    }*/
}
