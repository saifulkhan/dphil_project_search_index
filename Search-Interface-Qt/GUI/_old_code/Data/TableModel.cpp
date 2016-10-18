#include "TableModel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{

}


TableModel::TableModel (QList <File_S> fileList, QObject *parent) : QAbstractTableModel(parent)
{
    _fileList = fileList;
}


int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _fileList.size ();
}


int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 8;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= _fileList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        File_S file = _fileList.at (index.row());

        switch ( index.column() )
        {
        case 0:
            return file.id;
        case 1:
            return file.url;
        case 2:
            return file.name;
        case 3:
            return file.type;
        case 4:
            return file.size;
        case 5:
            return file.date;
        case 6:
            return file.rank;
        case 7:
            return file.axis;
        }
    }

    return QVariant();
}

 QVariant TableModel::headerData (int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal)
     {
         switch (section)
         {
         case 0:
             return "ID";
         case 1:
             return "URL";
         case 2:
             return "Name";
         case 3:
             return "Type";
         case 4:
             return "Size";
         case 5:
             return "Date";
         case 6:
             return "Rank";
         case 7:
             return "Axis";
         default:
             return QVariant();
         }
     }

    return QVariant();
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();

        File_S file = _fileList.value (row) ;

        switch ( index.column() )
        {
        case 0:
            file.id = value.toLongLong();
            break;
        case 1:
            file.url = value.toString();
            break;
        case 2:
            file.name = value.toString();
            break;
       case 3:
            file.type =value.value <FileType_E> () ;
            //role = QIcon (Data::_fileIcon (file.type)), Qt::DecorationRole
            break;
        case 4:
            file.size = value.toDouble();
            break;
        case 5:
            file.date = value.toDateTime();
            break;
        case 6:
            file.rank = value.toDouble();
            break;
        case 7:
            file.axis = value.toPointF();
            break;
        default:
            return false;
        }

        _fileList.replace (row, file);
        _fileList.value (row);

        emit ( dataChanged (index, index) );

        return true;
    }

    return false;
}


 bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; row++)
     {
         File_S file;
         _fileList.insert (position, file);
     }

     endInsertRows();
     return true;
 }


 bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row)
     {
         _fileList.removeAt (position);
     }

     endRemoveRows();
     return true;
 }


 QList <File_S> TableModel::getList()
 {
     return _fileList;
 }


 /**
   * Find the appropiate icon for the file type.
   */

 QString TableModel::_fileIcon (const FileType_E &fileType)
 {
     QString path =":/Resources/icons/";
     switch (fileType)
     {
     case txt:
         return path + "text-icon.png";
     case html:
         return path + "url-icon.png";
     case xml:
         return path + "url-icon.png";
     case pdf:
         return path + "pdf-icon.png";
     case cpp:
         return path + "source_cpp.png";
     case hpp:
         return path + "source_h.png";
     case tex:
         return path + "text-x-bibtex.png";

     case other:
         return path + "System-Unknown-icon.png";

     default:
         return path + "System-Unknown-icon.png";
         qDebug() << " Data::_fileIcon:" << fileType << endl;
         //Q_ASSERT(false);
     }
 }
