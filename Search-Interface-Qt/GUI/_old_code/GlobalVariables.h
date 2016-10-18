#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H


#include <QtGui>
#include <QBrush>

#include "Glyph/Secondary.h"
#include "Glyph/Animation.h"


// Version
#define VERSION V0.3


// Data

#define DATA ":/Resources/data/result.txt"

// VisWindow size
#define SCENE_WIDTH (QApplication::desktop()->availableGeometry().width() - 200)
#define SCENE_HEIGHT (QApplication::desktop()->availableGeometry().height() - 200)
#define VISWINDOW_COLOR Qt::black


#define ADJUST 0.5

// Primary (Static Properties)
#define PRI_DEF_SIZE 3			// Default
#define PRI_MAX_SIZE 50

//// Secondary (Static Properties)
//#define SEC_DEF_SIZE 8        // Default
//#define SEC_MAX_SIZE 125
//#define DEF_COLOR Qt::cyan


using namespace std;

typedef struct PrimaryProperty_S
{
    double size;
    QColor color;
    Qt::BrushStyle style;
    QPointF axis;

    PrimaryProperty_S (double size = PRI_DEF_SIZE, QColor color = DEF_COLOR, Qt::BrushStyle style =  Qt::SolidPattern, QPointF axis = QPointF ())
    {
        this->size = size;
        this->color = color;
        this->style = style;
        this->axis =  axis;
    }

    PrimaryProperty_S &operator= (const PrimaryProperty_S &p)
    {
        this->size = p.size;
        this->color = p.color;
        this->style = p.style;
        this->axis = p.axis;
        return *this;
    }

    PrimaryProperty_S (const PrimaryProperty_S &p)
    {
        this->size = p.size;
        this->color = p.color;
        this->style = p.style;
        this->axis = p.axis;
    }

    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

} PrimaryProperty_S;

Q_DECLARE_METATYPE (PrimaryProperty_S)


typedef struct Properties_S
{
    PrimaryProperty_S pri;
    Secondary sec;
    Animation an;

    Properties_S (PrimaryProperty_S pri, Secondary sec, Animation an)
    {
        this->pri = pri;
        this->sec = sec;
        this->an = an;
    }


    Properties_S ()
    {
        this->pri = PrimaryProperty_S ();
        this->sec = Secondary ();
        this->an = Animation ();
    }


    Properties_S &operator= (const Properties_S &p)
    {
        this->pri = p.pri;
        this->sec = p.sec;
        this->an = p.an;

        return *this;
    }

    Properties_S (const Properties_S &p)
    {
        this->pri = p.pri;
        this->sec = p.sec;
        this->an = p.an;
    }

    operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

} Properties_S;
Q_DECLARE_METATYPE(Properties_S)

inline QDebug operator<< (QDebug debug, const Properties_S& p)
{
    debug.nospace() << "Properties_S("
        << p.pri << ","
        << p.sec << ","
        << p.an << ")";
    return debug.space();
}


enum FileType_E {txt, html, xml, pdf, tex, cpp, hpp, other};
Q_DECLARE_METATYPE (FileType_E)

typedef struct File_S
{
    long long id;
    QString url;
    QString name;
    FileType_E type;
    double size;
    QDateTime date;
    double rank;

    QPointF axis;

    File_S (long long id = 0, QString url = " ",  QString name = " ",
            FileType_E type = other, double size = 0, QDateTime date = QDateTime (),
            double rank = 0, QPointF axis = QPointF ())
    {
        this->id = id;
        this->url = url;
        this->name = name;
        this->type = type;
        this->size = size;
        this->date = date;
        this->rank = rank;
        this->axis = axis;
    }

    File_S &operator= (const File_S &p)
    {
        this->id = p.id;
        this->url = p.url;
        this->name = p.name;
        this->type = p.type;
        this->size = p.size;
        this->date = p.date;
        this->rank = p.rank;
        this->axis = p.axis;

        return *this;
    }

    File_S (const File_S &p)
    {
        this->id = p.id;
        this->url = p.url;
        this->name = p.name;
        this->type = p.type;
        this->size = p.size;
        this->date = p.date;
        this->rank = p.rank;

        this->axis = p.axis;
    }

} File_S;


typedef struct FileStat_S
{
    double minSize;
    double maxSize;
    unsigned types;
    QDateTime minDate;
    QDateTime maxDate;
    double minRank;
    double maxRank;

    FileStat_S (double minSize = 0, double maxSize = 0, unsigned types = 0,
              QDateTime minDate = QDateTime (), QDateTime maxDate = QDateTime (),
              double minRank = 0, double maxRank = 0)
    {
        this->minSize = minSize;
        this->maxSize = maxSize;
        this->types = types;
        this->minDate = minDate;
        this->maxDate = maxDate;
        this->minRank = minRank;
        this->maxRank = maxRank;
    }

    FileStat_S &operator= (const FileStat_S &p)
    {
        this->minSize = p.minSize;
        this->maxSize = p.maxSize;
        this->types = p.types;
        this->minDate = p.minDate;
        this->maxDate = p.maxDate;
        this->minRank = p.minRank;
        this->maxRank = p.maxRank;

        return *this;
    }

    FileStat_S (const FileStat_S &p)
    {
        this->minSize = p.minSize;
        this->maxSize = p.maxSize;
        this->types = p.types;
        this->minDate = p.minDate;
        this->maxDate = p.maxDate;
        this->minRank = p.minRank;
        this->maxRank = p.maxRank;
    }

} FileStat_S;


enum VisAttr_E {PriColor, SecColor, SecSize, SecShape, SecAn};
enum FileAttr_E {Default, Type, Size, Date, Rank};


// Function Prototypes

QString enumToQString (const FileType_E &);
void popupMsg (const QString &, const QString &);

#endif // GLOBALVARIABLES_H
