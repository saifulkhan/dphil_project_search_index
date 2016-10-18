#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QPair>
#include <QList>

#include "GlobalVariables.h"

using namespace std;

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

 private:
    QList< QPair<QString, QString> > listOfPairs;
    QList <File_S> _fileList;

 public:
    /// Overloaded Functions

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());


    TableModel (QObject *parent=0);
    TableModel ( QList <File_S> fileList, QObject *parent=0);
    QList <File_S> getList();
    QString _fileIcon (const FileType_E &);


 };



#endif // TABLEMODEL_H
