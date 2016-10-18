#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <vector>
#include <QAbstractTableModel>
#include <QTableView>
#include <QItemDelegate>
#include <QPainter>
#include <QDateTime>
#include <FileInfo.h>

using namespace std;

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    vector<FileInfoX> m_fileInfoVec;
    int m_colNumWithCheckBox;
    QString fileIcon (const QString &type);
    static vector <string> m_metadata;

protected:
    // Overloaded virtual methods
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

public:

    TableModel(QObject *parent=0);
    TableModel(vector<FileInfoX> fileInfoVec, QObject *parent=0);
    vector<FileInfoX> getData() const { return m_fileInfoVec; }
};

#endif // TABLEMODEL_H
