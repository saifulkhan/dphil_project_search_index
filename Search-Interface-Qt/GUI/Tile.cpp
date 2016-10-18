#include "Tile.h"


/**
 * Tile: The function tileItem creates Tile.
 * Each tile is added as a children to its parent directory (? lang).
 **/

Tile::Tile(FileInfo _fileInfo, int _depth, int _maxdepth, QRectF _bound, QGraphicsItem *parent) :
           fileInfo( _fileInfo ), depth( _depth), maxdepth( _maxdepth ), QGraphicsItem(parent),
           bound(_bound)
{
    lastcolour = colour =  getColour();
    setAcceptHoverEvents(true);
    QString path = QString::fromStdString(fileInfo.m_path);

    setToolTip( path );
    setCacheMode( QGraphicsItem::DeviceCoordinateCache, bound.size().toSize() );
}


Tile::~Tile ()
{

}


QRectF Tile::boundingRect() const
{
    return QRectF( bound );
}


void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setClipRect( option->exposedRect );

    // Antialiazing ON-OFF
    if (false)
        painter->setRenderHints( QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing, true );

    // Boundary
    QColor tl1 = blendColor(colour, Qt::white, 0.6);

    painter->setPen(tl1);
    painter->setBrush(colour);
    painter->drawRect(bound);

    // Check if it is a directory (not so good way). Draw the text
    if (fileInfo.m_type.compare("") == 0)
    {
        QFont font("Monospace", TREEMAP_FONT_SIZE);
        //font.setCapitalization(QFont::AllUppercase);
        painter->setPen(Qt::black);
        painter->setFont(font);

        QFontMetrics fm(font);
        double wt = static_cast <double> (fm.width( QString::fromStdString(fileInfo.m_fileName)));
        double ht = static_cast <double> (fm.height());

         // Even if crosses the width, now gets clipped.
        if (depth <= 4 && bound.height() > ht && bound.width() > wt)
            painter->drawText( bound, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, QString::fromStdString(fileInfo.m_fileName));
    }
}


QColor Tile::blendColor( QColor a, QColor b, qreal alpha )
{
    int aR, aG, aB, aAlpha;
    int bR, bG, bB, bAlpha;
    int outR, outG, outB, outAlpha;

    a.getRgb( &aR, &aG, &aB, &aAlpha );
    b.getRgb( &bR, &bG, &bB, &bAlpha );

    outR = alpha * aR + (1 - alpha) * bR;
    outG = alpha * aG + (1 - alpha) * bG;
    outB = alpha * aB + (1 - alpha) * bB;
    outAlpha = alpha * aAlpha + (1 - alpha) * bAlpha;

    return QColor::fromRgb( outR, outG, outB, outAlpha );
}


void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Treemap");
    msgBox.setText("Node Details");
    char* size = convertSizeUnit(fileInfo.m_size);
    msgBox.setInformativeText( QString( "Path: %1 \nName: %2 \nSize: %3 \nModified: %4" )
                               .arg(QString::fromStdString(fileInfo.m_path))
                               .arg(QString::fromStdString(fileInfo.m_fileName))
                               .arg(size)
                               .arg(QString::fromStdString(fileInfo.m_lastModified)));

    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();

    delete size;
    //QGraphicsItem::mousePressEvent (event);
}


QColor Tile::getColour()
{
    /// File: Dark-purple
    if (fileInfo.m_type.compare("") != 0 )
    {
        switch (depth)
        {
        case 0:
            return QColor::fromRgb(136,65,157);
        case 1:
            return QColor::fromRgb(140,107,177);
        case 2:
            return QColor::fromRgb(140,150,198);
        case 3:
            return QColor::fromRgb(158,188,218);
        case 4:
            return QColor::fromRgb(191,211,230);
        default:
            return QColor::fromRgb(224,236,244);
        }
    }
    else /// Directory: Dark-green,
    {
        switch (depth)
        {
        case 0:
            return QColor::fromRgb(35,139,69);
        case 1:
            return QColor::fromRgb(65,174,118);
        case 2:
            return QColor::fromRgb(102,194,164);
        case 3:
            return QColor::fromRgb(153,216,201);
        case 4:
            return QColor::fromRgb(204,236,230);
        default:
            return QColor::fromRgb(229,245,249);
        }
    }

}


// Change the colour of the tiles, slows down the system
#if 0
void Tile::hoverEnterEvent( QGraphicsSceneHoverEvent *event )
{
    //colour = Qt::darkGray;
    //this->update();
}


void Tile::hoverLeaveEvent( QGraphicsSceneHoverEvent *event )
{
    //colour = lastcolour;
    //this->update();
}
#endif
