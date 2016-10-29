/*
 * TODO: Replace chache -> index
 * buildCache
 * add "IndexFile" methid as as mentioned in system overview workflow
 */



#ifndef IndexManager_H
#define IndexManager_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDesktopWidget> // Dont know about this header file. Added to avoid Qt5 compilation error.
#include <QApplication>
#include <QSettings>
#include <QFileDialog>
#include <string>

#include <Index.h>
#include <FileInfo.h>

#include "ui_IndexManager.h"

using namespace SE;

class IndexManager : public QDialog
{
    Q_OBJECT
private:
    Ui::IndexManager* ui;
    Index* m_cache;
    void buildCache();

public:
    explicit IndexManager(QDialog* parent = 0);
    ~IndexManager();

private slots:
    void on_applyButton_clicked();
};


#endif // IndexManager_H
