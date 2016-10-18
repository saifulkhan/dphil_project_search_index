#include "Data.h"


Data::Data (QString &arg)
{
     _dataFileName = arg;

     _parseData ();
     _prepareStat ();
}


void Data::_parseData ()
{

    if (_dataFileName.isNull () || _dataFileName.isEmpty ())
    {
        qFatal("FATAL-ERROR: Data::setupModel. 1 ");
    }

    QFile fd (_dataFileName);
    if (!fd.open (QFile::ReadOnly | QFile::Text))
    {
        qFatal ("FATAL-ERROR: Data::setupModel. 2 ");
    }
    else
    {
        QTextStream stream (&fd);
        QString line;

        File_S file;
        do
        {
            line = stream.readLine ();
            if (!line.isEmpty ())
            {
                QStringList pieces = line.split(" | ", QString::SkipEmptyParts);

                // Populate the structure and add to vector.
                file.id = pieces.value(1).toLongLong();
                file.url = pieces.value(2);
                file.name = _parseName (file.url);
                file.type = _parseType (file.name);
                file.rank = abs ( pieces.value(3).toDouble() );
                file.size = pieces.value(4).toDouble();
                file.date = QDateTime::fromString (pieces.value(5), "dd MM yyyy");

                // Randomly assign the axis.
                //file.axis.setX(qrand() % SCENE_WIDTH);
                //file.axis.setY(qrand() % SCENE_HEIGHT);

                _fileList.push_back (file);

            }

        } while (!line.isEmpty ());
    }
    fd.close ();
}


QString Data::_parseName (const QString &str)
{
   QStringList pieces = str.split("/", QString::SkipEmptyParts);
   return pieces.last();
}


FileType_E Data::_parseType (const QString &str)
{
    QStringList pieces = str.split(".", QString::SkipEmptyParts);

    if(pieces.last() == "txt")
        return txt;
    else if(pieces.last() == "html" || pieces.last() == "htm")
        return html;
    else if(pieces.last() == "xml")
        return xml;
    else if(pieces.last() == "pdf")
        return pdf;
    else if(pieces.last() == "c" || pieces.last() == "cpp")
        return cpp;
    else if(pieces.last() == "h" || pieces.last() == "hpp")
        return hpp;

    else
        return other;
}


QList <File_S> Data::getFileList ()
{
    return _fileList;
}


void Data::_prepareStat ()
{
    if (_fileList.empty())
    {
        return;
    }

    _sizeStat ();
    _dateStat ();
    _rankStat ();

    _fileStat.types = static_cast <int> (other + 1);
}


void Data::_sizeStat ()
{
    _fileStat.minSize = _fileStat.maxSize = _fileList.at(0).size;

    for (int i = 1; i < _fileList.size(); i++)
    {
        if ( _fileStat.minSize > _fileList.at(i).size )
        {
            _fileStat.minSize = _fileList.at(i).size;
        }

        if ( _fileStat.maxSize < _fileList.at(i).size )
        {
             _fileStat.maxSize = _fileList.at(i).size;
        }

    }
}


void Data::_dateStat ()
{
    _fileStat.minDate = _fileStat.maxDate = _fileList.at(0).date;

    for (int i = 1; i < _fileList.size(); i++)
    {
        if ( _fileStat.minDate > _fileList.at(i).date )
        {
            _fileStat.minDate = _fileList.at(i).date;
        }

        if (  _fileStat.maxDate < _fileList.at(i).date )
        {
              _fileStat.maxDate = _fileList.at(i).date;
        }

    }
}


void Data::_rankStat ()
{
    _fileStat.minRank = _fileStat.maxRank = _fileList.at(0).rank;

    for (int i = 1; i < _fileList.size(); i++)
    {
        if ( _fileStat.minRank > _fileList.at(i).rank )
        {
            _fileStat.minRank = _fileList.at(i).rank;
        }

        if (  _fileStat.maxRank < _fileList.at(i).rank )
        {
              _fileStat.maxRank = _fileList.at(i).rank;
        }

    }
}


FileStat_S Data::getFileStat ()
{
    return _fileStat;
}
