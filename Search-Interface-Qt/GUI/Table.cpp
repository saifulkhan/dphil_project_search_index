#include "Table.h"

vector <string> TableModel::m_metadata = {"Select", "Weight", "File Name", "Type", "Size", "Age", "Owner", "Group", "Path"};


TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{

}


TableModel::TableModel(vector<FileInfoX> fileInfoVec, QObject *parent) : QAbstractTableModel(parent)
{
    m_fileInfoVec = fileInfoVec;
    m_colNumWithCheckBox = 1;
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_fileInfoVec.size();
}


int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_metadata.size() + 1;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_fileInfoVec.size() || index.row() < 0)
        return QVariant();

    FileInfoX fileInfoX = m_fileInfoVec.at(index.row());

    if ( role == Qt::DisplayRole && index.column() == 0)
    {
         return index.row();
    }
    else if (role == Qt::CheckStateRole &&  index.column() == m_colNumWithCheckBox)
    {
        return (fileInfoX.m_select ? Qt::Checked : Qt::Unchecked);
    }
    else if (role == Qt::DisplayRole && index.column() >= 2)
    {
        switch (index.column())
        {
        case 2:
            return fileInfoX.m_weight;
        case 3:
            return QString::fromStdString(fileInfoX.m_fileInfo.m_fileName);
        case 4:
            return QString::fromStdString(fileInfoX.m_typex);
        case 5:
            return QString::fromStdString(fileInfoX.m_sizex);
        case 6:
            //return QDateTime::fromString(QString::fromStdString(fileInfoX.m_fileInfo.m_lastModified), Qt::ISODate);
            return QString::fromStdString(fileInfoX.m_agex);
        case 7:
            return QString::fromStdString(fileInfoX.m_fileInfo.m_user);
        case 8:
            return QString::fromStdString(fileInfoX.m_fileInfo.m_group);
        case 9:
            return QString::fromStdString(fileInfoX.m_fileInfo.m_path);
        default:
            Q_ASSERT_X(false, __PRETTY_FUNCTION__, "Something wrong here!");
        }
    }

    return QVariant();
}

 QVariant TableModel::headerData (int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal && section == 0)
     {
         return QString("Rank");
     }
     else if (orientation == Qt::Horizontal && section > 0)
     {
        #if DBG_GLYPH
        cout << __PRETTY_FUNCTION__ << FileInfoX::m_fileAttributes[section] << endl;
        #endif
        return QString::fromStdString(m_metadata[section - 1]);
     }

    return QVariant();
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == m_colNumWithCheckBox)
    {
            flags |= Qt::ItemIsUserCheckable;
            flags |= Qt::ItemIsEditable;
    }
    else
    {
        flags |= Qt::ItemIsSelectable;
    }
    return  flags;
}


/*
 * Update clicks inside fileinfo
 */
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();

    //cout << __PRETTY_FUNCTION__ << m_fileInfoVec[row].m_select;
    if (role == Qt::CheckStateRole && index.column() == m_colNumWithCheckBox)
    {
        if (value.toInt() == Qt::Checked)
            m_fileInfoVec[row].m_select = true;
        else if (value.toInt() == Qt::Unchecked)
            m_fileInfoVec[row].m_select = false;
    }
    //cout << __PRETTY_FUNCTION__ << m_fileInfoVec[row].m_select;

    QAbstractTableModel::setData(index,value);
    return true;
}
