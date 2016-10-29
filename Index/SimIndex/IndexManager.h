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

#include "ui_IndexManager.h"

class IndexManager : public QDialog
{
    Q_OBJECT
private:
    Ui::IndexManager* ui;
    SE::Index* m_index;
    string m_fileName;

    void buildIndex();

public:
    explicit IndexManager(QDialog* parent = 0);
    ~IndexManager();

private slots:
    void on_applyButton_clicked();
    void on_pushButton_selectFile_clicked();
};


#endif // CACHEMANAGER_H
