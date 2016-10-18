#ifndef INFOVIS_H
#define INFOVIS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include <QMainWindow>
#include <QtDebug>
#include <QtGui>
#include <QAbstractItemView>
#include <QFont>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QRect>
#include <QSize>
#include <QPoint>
#include <QWidget>
#include <QFile>
#include <QTranslator>
#include <QDateTime>

#include "GlobalVariables.h"


using namespace std;

class Data
{
private:
    QString _dataFileName;
    QList <File_S> _fileList;
    FileStat_S _fileStat;

    void _parseData ();
    void _prepareStat ();

    QString _parseName (const QString &);
    FileType_E _parseType (const QString &);
    void _sizeStat ();
    void _dateStat ();
    void _rankStat ();

public:
    Data (QString &);

    QList <File_S> getFileList ();
    FileStat_S getFileStat ();
};

#endif // INFOVIS_H
