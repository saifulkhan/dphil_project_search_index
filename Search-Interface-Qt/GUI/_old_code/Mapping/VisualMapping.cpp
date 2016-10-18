#include "VisualMapping.h"

VisualMapping::VisualMapping (QWidget *parent) : QDialog (parent), ui (new Ui::VisualMapping)
{
    ui->setupUi (this);
}


void VisualMapping::_updateProperty ()
{
    _channelMap = ui->channelMappingTab->getProperty();
    _typeMap = ui->typeMappingTab->getProperty();

}


///////////////////////////////////////////////////////////////////////////////
//
// Process PrimaryProperty
//
///////////////////////////////////////////////////////////////////////////////

PrimaryProperty_S VisualMapping::getPriProperty (const File_S &file)
{
    _updateProperty ();

    PrimaryProperty_S primaryProperty;
    primaryProperty.color = _getPrimaryColor (_channelMap[PriColor], file);

    return primaryProperty;
}


QColor VisualMapping::_getPrimaryColor (const FileAttr_E &attr, const File_S &file)
{

    QColor color;
    //qreal hue = 1.0, saturation = 1.0, value = 1.0;
    //int relold, datespan = _fileStat.minDate.daysTo (_fileStat.maxDate);

    switch (attr)
    {
    case Default:
        color = DEF_COLOR;
        break;

    case Type:
        color = _typeMap[file.type].pri.color;
        break;

    case Size:
        color = DEF_COLOR;
        //color = _secColorMap->lookupRGB (file.size, _fileStat.minSize, _fileStat.maxSize);
        break;

    case Date:
        color = DEF_COLOR;
        //relold = _fileStat.minDate.daysTo (file.date);
        //saturation =  (qreal) relold / (qreal) datespan;
        //qDebug() << "Date: " << saturation << endl;
        //color.setHsvF (hue, saturation, value);
        //color = _secColorMap->lookupHSV(hue, saturation, value);
        break;

    case Rank:
        color = DEF_COLOR;
        break;

    default:
        Q_ASSERT (false);
    }

    return color;
}


///////////////////////////////////////////////////////////////////////////////
//
// Process SecondaryProperty
//
///////////////////////////////////////////////////////////////////////////////

Secondary VisualMapping::getSecProperty (const File_S &file)
{
    _updateProperty ();

    Secondary sec;

    sec.color = _getSecondaryColor (_channelMap[SecColor], file);
    sec.size = _getSecondarySize (_channelMap[SecSize], file);
    sec.setType ( _getSecondaryShape (_channelMap[SecShape], file) );

    return sec;
}


QColor VisualMapping::_getSecondaryColor (const FileAttr_E &attr, const File_S &file)
{
    QColor color = DEF_COLOR;

    //qreal hue = 1.0, saturation = 1.0, value = 1.0;
    //int relold, datespan = _fileStat.minDate.daysTo (_fileStat.maxDate);

    switch (attr)
    {
    case Default:
         break;

    case Type:
        color = _typeMap[file.type].sec.color;
        break;

    case Size:
         //color = _secColorMap->lookupRGB (file.size, _fileStat.minSize, _fileStat.maxSize);
        break;

    case Date:

        //relold = _fileStat.minDate.daysTo (file.date);
        //saturation =  (qreal) relold / (qreal) datespan;
        //qDebug() << "Date: " << saturation << endl;
        //color.setHsvF (hue, saturation, value);
        //color = _secColorMap->lookupHSV(hue, saturation, value);
        break;

    case Rank:
        break;

    default:
        Q_ASSERT (false);
    }

    return color;
}


QSizeF VisualMapping::_getSecondarySize (const FileAttr_E &attr, const File_S &file)
{
    QSizeF size = QSizeF (SEC_DEF_SIZE, SEC_DEF_SIZE);

    switch (attr)
    {
    case Default:
        break;

    case Type:
        size = _typeMap[file.type].sec.size;
        break;

    case Size:
        break;

    case Date:
        break;

    case Rank:
        break;

    default:
        Q_ASSERT (false);
    }

    return size;
}



QString VisualMapping::_getSecondaryShape (const FileAttr_E &attr, const File_S &file)
{
    QString gtype = "Circle";

    switch (attr)
    {
    case Default:
        break;

    case Type:
        gtype = _typeMap[file.type].sec.getTypeString();
        break;

    case Size:
        break;

    case Date:
        break;

    case Rank:
        break;

    default:
        Q_ASSERT (false);
    }

    return gtype;
}


///////////////////////////////////////////////////////////////////////////////
//
// Process AnimationProperty
//
///////////////////////////////////////////////////////////////////////////////


Animation VisualMapping::getAnProperty(const File_S & file)
{
    _updateProperty ();

    Animation an;
    an = _getAnProperty (_channelMap[SecAn], file);
    return an;
}


Animation VisualMapping::_getAnProperty (const FileAttr_E &attr, const File_S &file)
{
    Animation an;

    switch (attr)
    {
    case Default:
        break;

    case Type:
        an = _typeMap[file.type].an;
        break;

    case Size:
        break;

    case Date:
        break;

    case Rank:
        break;

    default:
        Q_ASSERT (false);
    }

    return an;
}


void VisualMapping::on_applyButton_clicked()
{
    _updateProperty ();
    qDebug() << "VisualMapping:: Mapping changed signal emited...";
    emit VisualMapping_Signal ();
}


void VisualMapping::on_okButton_clicked()
{
   on_applyButton_clicked();
   this->close();
}


void VisualMapping::on_cancelButton_clicked()
{
    this->close();
}




#if 0
ColourMap* Mapping::_initColorMap (ColourLookUp clut)
{
    QGraphicsView *view = new QGraphicsView ();
    QGraphicsScene *scene = new QGraphicsScene ();
    view->setScene (scene );
    scene->setSceneRect ( QRectF(0, 0, 200, 10) );
    scene->setItemIndexMethod (QGraphicsScene::NoIndex);

    ColourMap *colormap = new ColourMap ( clut, 300.0, 10.0);
    colormap->setPos (0, 0);
    scene->addItem (colormap );
    view->show();

    return colormap;
}
#endif
