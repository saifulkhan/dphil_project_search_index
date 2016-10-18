#include "Mapping.h"

Mapping::Mapping(QGraphicsScene *_scene, QDialog *parent) : scene(_scene), QDialog(parent), ui (new Ui::Mapping)
{
    ui->setupUi(this);
    colourMap = NULL;
    m_treemap = Treemap::instance(scene);

    connect(m_treemap, SIGNAL ( signal_Treemap(bool)), this, SLOT ( slot_Treemap(bool)));
}


Mapping::~Mapping()
{

}


void Mapping::startMapping(const vector<FileInfoX> &fileInfoVec)
{
    // Clear the previous visualisation, if already there.
    m_fileInfoVec.clear();
    clearMapping();

    m_fileInfoVec = fileInfoVec;
    for (int i = 0; i < m_fileInfoVec.size(); ++i)
    {
        FileInfoX fileInfo = m_fileInfoVec[i];
        string fileFullPath = fileInfo.m_fileInfo.m_path + "/" + fileInfo.m_fileInfo.m_fileName;
        RectF rectF = m_treemap->coordinate(fileFullPath);
        QRectF coordinate(rectF.x(), rectF.y(), rectF.width(), rectF.height());
        mapSize(fileInfo, coordinate.center());
        mapDate(fileInfo, coordinate.center());
        mapTime(fileInfo, coordinate.center());
        mapType(fileInfo, coordinate.center());
        mapPermission(fileInfo, coordinate.center());
    }
}

/*
 * Remove the existing items form the scene.
 * clear the glyph the vectors.
 * Call this before a fresh mapping of new search result
 */

void Mapping::clearMapping()
{
    foreach ( SizeGlyph *g, sizeGlyphVec )
        scene->removeItem( g );
    sizeGlyphVec.clear();

    foreach ( TypeGlyph *g, typeGlyphVec )
        scene->removeItem( g );
    typeGlyphVec.clear();

    foreach ( DateGlyph *g, dateGlyphVec )
        scene->removeItem( g );
    dateGlyphVec.clear();

    foreach ( TimeGlyph *g, timeGlyphVec )
        scene->removeItem( g );
    timeGlyphVec.clear();

    foreach ( PermissionGlyph *g, permissionGlyphVec )
        scene->removeItem( g );
    permissionGlyphVec.clear();
}

/*
 * When the m_treemap's size/coordinate changes, then the glyphs also need to reposition
 */

void Mapping::resetCoordinate()
{
    for (int i = 0; i < m_fileInfoVec.size(); i ++ )
    {
        string fileFullPath = m_fileInfoVec[i].m_fileInfo.m_path + "/" + m_fileInfoVec[i].m_fileInfo.m_fileName;
        RectF rectF = m_treemap->coordinate(fileFullPath);
        QRectF coordinate(rectF.x(), rectF.y(), rectF.width(), rectF.height());
        sizeGlyphVec[i]->setPos( coordinate.center() );
        typeGlyphVec[i]->setPos( coordinate.center() );
        dateGlyphVec[i]->setPos( coordinate.center() );
        timeGlyphVec[i]->setPos( coordinate.center() );
        permissionGlyphVec[i]->setPos( coordinate.center() );
    }
}



void Mapping::slot_Treemap(bool)
{
    qDebug() << __PRETTY_FUNCTION__;
    resetCoordinate();
}

void Mapping::notifyClickEvent(const FileInfoX &fileInfo)
{
    qDebug() << __PRETTY_FUNCTION__;
    emit signal_RelavanceFeddback(fileInfo);
}


/*
 * ********************************** Mapping  **********************************************
 */

/*
 * 40px max size of the pie. 5px difference we can perceive easily, that gives 8 different sizes.
 * Now, map size of the file to 8 different scales.
 */

void Mapping::mapSize(const FileInfoX &fileInfo, const QPointF &center )
{
    int quadrant;
    double start = 0;
    double stop;

    string type = tokenise(fileInfo.m_sizex, " ").back();
    int    size = atoi(tokenise(fileInfo.m_sizex, " ").front().c_str());

    if (type.compare("GB") == 0)
        quadrant = 4;
    else if (type.compare("MB") == 0)
        quadrant = 3;
    else if (type.compare("KB") == 0)
         quadrant = 2;
    else if (type.compare("B") == 0)
        quadrant = 1;

    stop = normalizeScale(256, 0.25, size);

    SizeGlyph *sizeGlyph = new SizeGlyph(center, QSizeF(stop * 80, stop * 80), 0, 1, quadrant);
    scene->addItem(sizeGlyph);
    sizeGlyphVec.push_back(sizeGlyph);
}


void Mapping::mapType(const FileInfoX &fileInfo, const QPointF &center )
{
    QColor color = getColor(fileInfo);
    //qDebug() << __PRETTY_FUNCTION__ << "RGB=" << color.red() << "," << color.green() << "," << color.blue();
    TypeGlyph *typeGlyph = new TypeGlyph( center, QSizeF(5, 5), color, fileInfo );
    scene->addItem(typeGlyph);
    typeGlyphVec.push_back(typeGlyph);
    typeGlyph->registerObserver(this);
    //connect(typeGlyphVec.back(), SIGNAL(signal_TypeGlyph(FileInfoX fileInfo)), this, SLOT(slot_TypeGlyph(FileInfoX fileInfo)));
}

/*
 * TODO:
 * Follow the spreadsheet created in draft/CAG folder
 Spreadsheets / Presentations: Cyan
 Documents / Acrobats : Blue
 Images: Magenta
 Audio/Video: Orange
 Archives: Light-Pink
 Codes : Yellow
 System/Exes : Gray
 */

QColor Mapping::getColor(const FileInfoX &fileInfo)
{
    if ( ui->typeComboBox->currentText() == QString("Hierarchy-0") )
        return Qt::white;

    string ext = fileInfo.m_fileInfo.m_type;
    //qDebug() << __PRETTY_FUNCTION__ << ui->typeComboBox->currentText() << ", " << ext;


    /// spreadsheets / presentations
    if ( ext == "xls" || ext == "xlsx" || ext == "ppt" || ext == "pptx") {
        if ( ui->typeComboBox->currentText() == QString("Hierarchy-1") )
            return QColor(255, 255, 255);   // white
        else
            return QColor(0, 255, 255);     // Cyan
    }

    /// documents
    if ( ext == "txt" || ext == "doc" || ext == "docx" || ext == "rtf" || ext == "tex" || ext == "bbl" || ext == "html" || ext == "htm" || ext == "pdf" || ext == "ps") {
        if ( ui->typeComboBox->currentText() == QString("Hierarchy-1") )
            return QColor(255, 255, 255);   // white
        else
            return QColor( 0, 0, 255 );    // Blue
    }

    /// images
    if ( ext == "png" || ext == "nef" || ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "tif" || ext == "tiff" ||
         ext == "bmp" || ext == "xpm" || ext == "tga" || ext == "psd") {
        if (ui->typeComboBox->currentText() == QString("Hierarchy-1"))
            return QColor(255, 255, 255);   // white
        else
            return QColor(255, 0, 255);     // Magenta
    }

    // audio / video

    if ( ext == "wav" || ext == "mp3" || ext == "avi"  || ext == "f4v" || ext == "mov" || ext == "3gp" || ext == "3ga"  ||
         ext == "mpg" || ext == "m4v" || ext == "mpeg" || ext == "mp4" || ext == "flv" ) {
        if ( ui->typeComboBox->currentText() == QString("Hierarchy-1") )
            return QColor(255, 255, 255);   // white
        else
            return QColor(255, 165, 0);     // Orange
    }

    /// archives
    if (ext == "zip" || ext == "tar.bz2" || ext == "tar.gz" || ext == "tgz" || ext == "bz2" || ext == "bz" || ext == "gz") {
        if (ui->typeComboBox->currentText() == QString("Hierarchy-1"))
            return QColor(255, 255, 255);   // white
        else
            return QColor(255, 182, 193);   // lightPink
    }

    /// codes
    if ( ext == "c" || ext == "cpp" || ext == "cc" || ext == "h" || ext == "hpp" || ext == "moc.cpp" || ext == "moc.cc" ) {

        if ( ui->typeComboBox->currentText() == QString("Hierarchy-1") )
            return QColor(255, 255, 255);   // white
        else
            return QColor(255, 255,   0);   // yellow
    }


    /// System
    if (ext == "bak" || ext == "sqlite3" || ext == "sql" || ext == "exe" || ext == "com" || ext == "dll" || ext == "arj" ||
        ext == "o"	 || ext == "lo"      || ext == "Po"  || ext == "al"  || ext == "elc" || ext == "la"  || ext == "a"	 ||
        ext == "rpm" || ext == "~"       || ext == "el"  || ext == "jar") {
            return QColor(220, 220, 220);   // grey
    }

    /// Other
    return QColor(255, 255, 255);  // White
}


void Mapping::mapDate(const FileInfoX &fileInfo, const QPointF &center)
{
    int quadrant = 0;
    qreal rotate = 0;
    DateGlyph *dateGlyph;

/*  int fileYear = 0;
    int fileMonth = 0;
    int fileDay = 0;
    int todayYear = 0;
    int todayMonth = 0;
    int todayDay = 0;

    QDateTime todayDate = QDateTime::currentDateTime();

    QString str;
    if (ui->dateComboBox->currentIndex() == 0)
        str = QString::fromStdString(fileInfo.m_fileInfo.m_lastModified);
    else if (ui->dateComboBox->currentIndex() == 1)
        str = QString::fromStdString(fileInfo.m_fileInfo.m_lastRead);
    else if (ui->dateComboBox->currentIndex() == 2)
        str = QString::fromStdString(fileInfo.m_fileInfo.m_created);
    else
        Q_ASSERT(false);
    QDateTime fileDate = QDateTime::fromString(str, Qt::ISODate);

    fileDate.date().getDate( &fileYear, &fileMonth, &fileDay );         // Get year, month, day
    todayDate.date().getDate( &todayYear, &todayMonth, &todayDay);


    int days = fileDate.daysTo( todayDate );
    int months = days / 30;
    int years = todayYear - fileYear;

    if ( years >= 10 ) {
        quadrant = 4;
        if ( years >= 100 )                                  // 100 years (10decade).
            rotate = normalizeScale( 16.667, 15, 100 );       // 90/15 (deg) = 6 segments, 100/6 = 16.667
        else
            rotate = normalizeScale( 16.667, 15, years );

    } else if ( years > 0 ) {                               // 1-10 year
        quadrant = 3;
        rotate = normalizeScale( 1.667, 15, years );         // 10/6 = 1.667

    } else if ( months >= 1) {                              // 1 - 12 month
        quadrant = 2;
        rotate = normalizeScale( 2, 15, months );            // 12/6 = 2
    } else if ( days >= 0 ) {                               // could start, stopbe today also so (>=) used
        quadrant = 1;
        rotate = normalizeScale( 5, 15, days );              // 30/6 = 5
    }

    if (rotate  < 0 || rotate > 90)
        Q_ASSERT(false);

    //qDebug() <<  __PRETTY_FUNCTION__ << "Name:" << fileInfo.m_fileInfo.fileName() << " Modified:" << fileDate.date() << ", quadrant/rotate" << quadrant << "/" << rotate;
*/

    string type = tokenise(fileInfo.m_agex, " ").back();
    int    age  = atoi(tokenise(fileInfo.m_agex, " ").front().c_str());

    if (type.compare("DE") == 0)
    {
        quadrant = 4;
        rotate = normalizeScale(16.667, 15, age);
    }
    else if (type.compare("Y") == 0)
    {
        quadrant = 3;
        rotate = normalizeScale(1.667, 15, age);    // 1-10 year 10/6 = 1.667; 6 degree(?)
    }
    else if (type.compare("M") == 0)
    {
        quadrant = 2;
        rotate = normalizeScale(2, 15, age);        // 1 - 12 month, 12/6 = 2
    }
    else if (type.compare("D") == 0)
    {
        quadrant = 1;
        rotate = normalizeScale( 5, 15, age);       // 30/6 = 5
    }

    dateGlyph = new DateGlyph(center, QSizeF(40, 40), quadrant, rotate);
    scene->addItem(dateGlyph);
    dateGlyphVec.push_back(dateGlyph);
}


void Mapping::mapTime( const FileInfoX &fileInfo, const QPointF &center )
{
    qreal start =0;
    qreal stop = 0;

    QString str;
    if (ui->dateComboBox->currentIndex() == 0)
        str = QString::fromStdString(fileInfo.m_fileInfo.m_lastModified);
    else if (ui->dateComboBox->currentIndex() == 1)
        str = QString::fromStdString(fileInfo.m_fileInfo.m_lastRead);
    else if (ui->dateComboBox->currentIndex() == 2)
        str = QString::fromStdString(fileInfo.m_fileInfo.m_created);
    else
        Q_ASSERT(false);
    QDateTime fileTime = QDateTime::fromString(str, Qt::ISODate);
    int hour = fileTime.time().hour();
    stop = normalize(0, 23, 0, 1, hour);

    //qDebug() << __PRETTY_FUNCTION__ << "Time=" << fileTime << ", Hour= " << hour;
    //qDebug() << "start=" << start << ", " << "stop=" << stop;

    TimeGlyph *timeGlyph = new TimeGlyph( center, QSizeF(30, 30), start, stop );
    scene->addItem(timeGlyph);
    timeGlyphVec.push_back(timeGlyph);
}


void Mapping::mapPermission( const FileInfoX &fileInfo, const QPointF &center )
{
    PermissionGlyph *permissionGlyph = new PermissionGlyph(center, QSizeF(15, 15) );
    scene->addItem(permissionGlyph);
    permissionGlyph->hide();
    permissionGlyphVec.push_back(permissionGlyph);
}


/*
 * ********************************** Control and settings  **********************************************
 */


void Mapping::on_typeComboBox_currentIndexChanged(int index)
{
    /*for (int i = 0; i < m_fileInfoVec.size(); i ++ ) {
        scene->removeItem( m_fileInfoVec[i].re );
        mapType( m_fileInfoVec[i], fileCoordinateVec[i].center() );
    }*/
}


void Mapping::on_dateComboBox_currentIndexChanged(int index)
{

}


void Mapping::on_typeShowCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach (TypeGlyph *it, typeGlyphVec )
            it->show();
    } else if (state == Qt::Unchecked) {
        foreach (TypeGlyph *it, typeGlyphVec )
            it->hide();
    }
}


void Mapping::on_sizeShowCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach ( SizeGlyph *it, sizeGlyphVec )
            it->show();
    } else if (state == Qt::Unchecked) {
        foreach ( SizeGlyph *it, sizeGlyphVec )
            it->hide();
    }

}


void Mapping::on_dateShowCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach ( DateGlyph *it, dateGlyphVec )
            it->show();
    } else if (state == Qt::Unchecked) {
        foreach ( DateGlyph *it, dateGlyphVec )
            it->hide();
    }
}


void Mapping::on_timeShowCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach ( TimeGlyph *it, timeGlyphVec )
            it->show();
    } else if (state == Qt::Unchecked) {
        foreach ( TimeGlyph *it, timeGlyphVec )
            it->hide();
    }
}


void Mapping::on_permissionShowCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach ( PermissionGlyph *it, permissionGlyphVec )
            it->show();
    } else if (state == Qt::Unchecked) {
        foreach ( PermissionGlyph *it, permissionGlyphVec )
            it->hide();
    }
}


void Mapping::on_typeAnCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach (TypeGlyph *it, typeGlyphVec )
            it->startAnimation();
    } else if (state == Qt::Unchecked) {
        foreach (TypeGlyph *it, typeGlyphVec )
            it->stopAnimation();
    }
}


void Mapping::on_sizeAnCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach (SizeGlyph *it, sizeGlyphVec )
            it->startAnimation();
    } else if (state == Qt::Unchecked) {
        foreach (SizeGlyph *it, sizeGlyphVec )
            it->stopAnimation();
    }
}


void Mapping::on_dateAnCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach (DateGlyph *it, dateGlyphVec )
            it->startAnimation();
    } else if (state == Qt::Unchecked) {
        foreach (DateGlyph *it, dateGlyphVec )
            it->stopAnimation();
    }
}


void Mapping::on_timeAnCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach (TimeGlyph *it, timeGlyphVec )
            it->startAnimation();
    } else if (state == Qt::Unchecked) {
        foreach (TimeGlyph *it, timeGlyphVec )
            it->stopAnimation();
    }
}


void Mapping::on_permissionAnCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        foreach (PermissionGlyph *it, permissionGlyphVec )
            it->startAnimation();
    } else if (state == Qt::Unchecked) {
        foreach (PermissionGlyph *it, permissionGlyphVec )
            it->stopAnimation();
    }
}


void Mapping::on_colormapButton_clicked()
{
    QGraphicsScene *tScene;
    QGraphicsView *tView;

    if ( colourMap == NULL ) {
        colourMap = new ColourMap( dayCLUT(), 500.0, 50.0);
        tScene = new QGraphicsScene();
        tView = new QGraphicsView(tScene);
        tScene->addItem(colourMap);
    }

    tView->show();
}

void Mapping::on_applyButton_clicked()
{
    qreal duration;
    QVector <QPair <double, double> > sizeTF;
    QVector <QPair <double, double> > dateTF;
    QVector <QPair <double, double> > timeTF;

    if ( ui->defaultGroupBox->isChecked() ) {
        duration = ui->defaultDurationSpinBox->value();
        sizeTF << QPair <double, double> (0, 0) <<
              QPair <double, double> (0.00001, 1) <<
              QPair <double, double> (0.7, 1) <<
              QPair <double, double> (0.70001, 0) <<
              QPair <double, double> (1, 0);

        timeTF << QPair <double, double> (0, 0) <<
               QPair <double, double> (0.1, 0) <<
               QPair <double, double> (0.10001, 1) <<
               QPair <double, double> (0.8, 1) <<
               QPair <double, double> (0.80001, 0) <<
               QPair <double, double> (1, 0);

        dateTF << QPair <double, double> (0, 0) <<
              QPair <double, double> (0.2, 0) <<
              QPair <double, double> (0.20001, 1) <<
              QPair <double, double> (0.9, 1) <<
              QPair <double, double> (0.90001, 0) <<
              QPair <double, double> (1, 0);

    } else if ( ui->customGroupBox->isChecked()) {
        duration = ui->customDurationSpinBox->value();
        sizeTF = ui->sizeTF->getTransferFunction();
        dateTF = ui->dateTF->getTransferFunction();
        timeTF = ui->timeTF->getTransferFunction();

    } else {
        Q_ASSERT( false );
    }

    foreach (SizeGlyph *it, sizeGlyphVec ) {
        it->resetAnimation(sizeTF, duration, "scale");
        ui->sizeAnCheckBox->setCheckState( Qt::Checked );
    }
    foreach (DateGlyph *it, dateGlyphVec ) {
        it->resetAnimation( dateTF, duration, "rotationZ" );
        ui->dateAnCheckBox->setCheckState( Qt::Checked );
    }
    foreach (TimeGlyph *it, timeGlyphVec ) {
        it->resetAnimation( timeTF, duration, "length" );
        ui->timeAnCheckBox->setCheckState( Qt::Checked );
    }
}


void Mapping::on_defaultGroupBox_clicked(bool checked)
{
    if (checked)
        ui->customGroupBox->setChecked(false);
    else
        ui->customGroupBox->setChecked(true);
}


void Mapping::on_customGroupBox_clicked(bool checked)
{
    if (checked)
        ui->defaultGroupBox->setChecked(false);
    else
        ui->defaultGroupBox->setChecked(true);
}

void Mapping::on_opacitySlider_valueChanged(int value)
{
    qreal opacity = (qreal) value / 10;
    ui->opacityLineEdit->setText( QString::number(opacity) );
    for (int i = 0; i < sizeGlyphVec.size(); i++) {
        sizeGlyphVec[i]->setOpacity( opacity );
        typeGlyphVec[i]->setOpacity( opacity );
        dateGlyphVec[i]->setOpacity( opacity );
        timeGlyphVec[i]->setOpacity( opacity );
        permissionGlyphVec[i]->setOpacity( opacity );
    }

}
