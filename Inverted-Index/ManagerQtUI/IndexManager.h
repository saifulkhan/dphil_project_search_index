/*
 * TODO: Replace chache -> index
 * buildCache
 * add "IndexFile" methid as as mentioned in system overview workflow
 */



#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDesktopWidget> // Dont know about this header file. Added to avoid Qt5 compilation error.
#include <QApplication>
#include <QSettings>
#include <QFileDialog>
#include <string>

#include <Index.h>
#include <FileInfo.h>

#include "ui_CacheManager.h"

class CacheManager : public QDialog
{
    Q_OBJECT
private:
    Ui::CacheManager* ui;
    Index* m_cache;
    void buildCache();

public:
    explicit CacheManager(QDialog* parent = 0);
    ~CacheManager();

private slots:
    void on_applyButton_clicked();
};


#endif // CACHEMANAGER_H
