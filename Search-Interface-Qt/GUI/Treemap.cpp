#include "Treemap.h"


Treemap* Treemap::m_treemap = NULL;


Treemap* Treemap::instance(QGraphicsScene *scene)
{
    if (!m_treemap)
        m_treemap = new Treemap(scene);
    return m_treemap;
}


Treemap::Treemap(QGraphicsScene *scene) : ui(new Ui::Treemap)
{
    ui->setupUi( this );
    this->scene         = scene;
    settings            = new QSettings( "TreemapSetting", "TreemapSetting" );
    m_rootNodeTM        = NULL;
    m_rootTile          = NULL;
    m_cacheParser       = new CacheParser();
}


Treemap::~Treemap()
{
    delete m_cacheParser;
}


/*********************************************************************************************************
 * Scan cache / disk
 *  1.   Build the tree of the filesystem first time and store in NodeTM structure.
 *       The tree can be created from Cache or Existing file system(by scaning it).
 *  1.a. Condition: Build/re-build the NodeTM only when first time treemap is built or the rootDir is changed
 *  2.   When scale, height, width etc changed by control window only new layout will be done,
 *       whre the NodeTM.rectF will only change
 *********************************************************************************************************/

void Treemap::buildTreemap()
{
    loadSettings();

    /*
     * Build/re-build the NodeTM only when first time treemap is built or the rootDir is changed
     */
    if ((m_rootNodeTM == NULL) || (m_rootDir != lastRootDir)) // (1), (1.a)
    {
        if (m_rootNodeTM)
            m_rootNodeTM->deleteAll(m_rootNodeTM);         // (1.a)

        if(m_cacheParser)
        {
            m_rootNodeTM = m_cacheParser->parse(m_rootDir.toStdString());
        }
        lastRootDir = m_rootDir;
    }

    /*
     * When scale, height, width etc changed by control window only new layout will be done,
     * whre the NodeTM.rectF will only change
     */
    m_layout.doLayout(m_rootNodeTM, RectF(0, 0, width, height));
    m_coordinate.clear();
    m_coordinate = m_layout.coordinate();

    #ifdef DBG_TREEMAP
    m_rootNodeTM->print(m_rootNodeTM);
    #endif

    /*
     * Create rentangle graphics
     */
    if (m_rootTile)
    {
        scene->removeItem(m_rootTile);
        delete m_rootTile;
    }
    m_rootTile = new Tile(m_rootNodeTM->fileInfo, m_rootNodeTM->depth, maxdepth,
                          QRectF(m_rootNodeTM->rectF.x(), m_rootNodeTM->rectF.y(), m_rootNodeTM->rectF.width(), m_rootNodeTM->rectF.height()),
                          0);  // root tile

    this->createTiles( m_rootNodeTM );
    m_rootTile->setZValue(-1);
    scene->addItem( m_rootTile );
}


void Treemap::createTiles( NodeTM* parentItem)
{
    #ifdef DBG_TREEMAP
    cout << __PRETTY_FUNCTION__ << "depth= " << parentItem->depth << ", maxdepth= " << maxdepth << ", Parent= " << parentItem->fileInfo.m_fileName;
    #endif

    foreach ( NodeTM* node, parentItem->children )
    {
        if (!this->filterItem(node))
        {
            Tile *tile = new Tile(node->fileInfo, node->depth, maxdepth,
                                  QRectF(node->rectF.x(), node->rectF.y(), node->rectF.width(), node->rectF.height()),
                                  m_rootTile);

        }
    }

    foreach ( NodeTM* node, parentItem->children )
    {
        if (node->children.size() > 0 )
            this->createTiles( node );
    }
}


bool Treemap::filterItem (NodeTM* item)
{
    double len = sqrt( (double)minscale );

    if (item->depth > maxdepth)
        return true;            // Filter beyond certain depth
    else if ( (item->rectF.width() < len) || (item->rectF.height() < len) )
        return true;            // Filter when their rectangles are too small
    else
        return false;
}


/*********************************************************************************************************
 *  Other Functions
 *********************************************************************************************************/

RectF Treemap::coordinate(const string& fileFullPath)
{
    RectF rect = m_coordinate[fileFullPath];

    #ifdef DBG_TREEMAP
    if (rect.x() == 0 || rect.y() == 0)
        cout << __PRETTY_FUNCTION__ << fileFullPath << ": Not-found in map: " << rect << endl;
    else
        cout << __PRETTY_FUNCTION__ << fileFullPath << ": Found in the map: " << rect << endl;
    #endif
    return rect;
}


/*********************************************************************************************************
 *  Setting/Signals-Slots
 *********************************************************************************************************/

void Treemap::loadSettings()
{
    m_rootDir = settings->value( "dir", "/mnt" ).toString();

    if (m_rootDir.isEmpty())
        Q_ASSERT_X (false, __PRETTY_FUNCTION__, "Dir is empty.");

    maxdepth    = settings->value( "maxdepth", 1 ).toInt();
    minscale    = settings->value( "minscale", 1 ).toInt();
    width       = settings->value( "width", 500 ).toInt();
    height      = settings->value( "height", 500 ).toInt();

    ui->rootLineEdit->setText( m_rootDir );
    ui->maxdepthSpinBox->setValue( maxdepth );
    ui->minscaleSpinBox->setValue( minscale );
    ui->widthSpinBox->setValue( width );
    ui->heightSpinBox->setValue( height );

}


void Treemap::saveSettings()
{
    QString text = ui->rootLineEdit->text().isEmpty() ? "/mnt" : ui->rootLineEdit->text();
    settings->setValue( "dir", text );
    settings->setValue( "maxdepth", ui->maxdepthSpinBox->value() );
    settings->setValue( "minscale", ui->minscaleSpinBox->value() );
    settings->setValue( "width", ui->widthSpinBox->value() );
    settings->setValue( "height", ui->heightSpinBox->value() );
}


void Treemap::on_browseButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory( this, tr("Open Directory"), "/home/saiful", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if ( dir.isEmpty())
        ui->rootLineEdit->setText( m_rootDir );
    else if ( !(dir == m_rootDir) )
        ui->rootLineEdit->setText( dir );
}


void Treemap::on_applyButton_clicked()
{
    this->saveSettings();
    this->buildTreemap();

    emit signal_Treemap(true);
}


/*********************************************************************************************************
 *  NOT IMPORTANT: Treemap from Filesystem
 *********************************************************************************************************/

void Treemap::scanFileSystem()
{
    QFileInfo qfileInfo( m_rootDir );
    if (!qfileInfo.isDir())
    {
        QMessageBox::warning(this, "Treemap", "Incorrect Directory", QMessageBox::Ok);
        return;
    }
    FileInfo fileinfo;
    fileinfo.m_fileName     = qfileInfo.fileName().toStdString();
    fileinfo.m_type         = qfileInfo.suffix().toStdString();
    fileinfo.m_path         = qfileInfo.absolutePath().toStdString();
    fileinfo.m_size         = qfileInfo.size();
    fileinfo.m_lastModified = qfileInfo.lastModified().toString(Qt::ISODate).toStdString();
    fileinfo.m_lastRead     = qfileInfo.lastRead().toString(Qt::ISODate).toStdString();
    fileinfo.m_created      = qfileInfo.created().toString(Qt::ISODate).toStdString();
    fileinfo.m_user         = qfileInfo.owner().toStdString();
    fileinfo.m_group        = qfileInfo.group().toStdString();

    m_rootNodeTM = new NodeTM(fileinfo, 0, 0 );
    qDebug() << __PRETTY_FUNCTION__ << "Started scanning file system: " << m_rootDir;
    this->scanFileSystem( QDir(m_rootDir), m_rootNodeTM);
    qDebug() << __PRETTY_FUNCTION__ << "Complete scanning file system: " << m_rootDir;

}


/*
 * Scan the file system from the specified root and create the Treemap data-structure (n-ary tree).
 *
 */

void Treemap::scanFileSystem (QDir dir, NodeTM* parent)
{
    /*
     * Get the list of files. Filter out the empty files. Add as the childrens.
     */
    FileInfo fileinfo;
    QFileInfo qfileInfo;

    dir.setFilter ( QDir::Readable | QDir::Files );
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); i++)
    {
        qfileInfo               = list.at(i);
        fileinfo.m_fileName     = qfileInfo.fileName().toStdString();
        fileinfo.m_type         = qfileInfo.suffix().toStdString();
        fileinfo.m_path         = qfileInfo.absolutePath().toStdString();
        fileinfo.m_size         = qfileInfo.size();
        fileinfo.m_lastModified = qfileInfo.lastModified().toString(Qt::ISODate).toStdString();
        fileinfo.m_lastRead     = qfileInfo.lastRead().toString(Qt::ISODate).toStdString();
        fileinfo.m_created      = qfileInfo.created().toString(Qt::ISODate).toStdString();
        fileinfo.m_user        = qfileInfo.owner().toStdString();
        fileinfo.m_group        = qfileInfo.group().toStdString();

        //qDebug() << __PRETTY_FUNCTION__ << " Appended(file)= " << qfileInfo.filePath() << ", Depth=" << parent->depth + 1;

        if ( qfileInfo.size() > 0 )
            parent->children.push_back(new NodeTM(fileinfo, parent->depth + 1, qfileInfo.size()));
    }

    /*
     * Get the list of directories. Filter empty dir. Add to the childrens. Scan this directory further.
     */

    dir.setFilter (QDir::Readable | QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirlist = dir.entryList();

    for (int i = 0; i < dirlist.size(); ++i)
    {
        QString newDir = QString("%1/%2").arg(dir.absolutePath()).arg(dirlist.at(i));
        QDir childdir = QDir( newDir );

        if (childdir.entryInfoList( QDir::Readable | QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks).size() > 0)
        {
            qfileInfo               = QFileInfo(newDir);
            fileinfo.m_fileName     = qfileInfo.fileName().toStdString();
            fileinfo.m_type         = qfileInfo.suffix().toStdString();
            fileinfo.m_path         = qfileInfo.absolutePath().toStdString();
            fileinfo.m_size         = qfileInfo.size();
            fileinfo.m_lastModified = qfileInfo.lastModified().toString(Qt::ISODate).toStdString();
            fileinfo.m_lastRead     = qfileInfo.lastRead().toString(Qt::ISODate).toStdString();
            fileinfo.m_created      = qfileInfo.created().toString(Qt::ISODate).toStdString();
            fileinfo.m_user        = qfileInfo.owner().toStdString();
            fileinfo.m_group        = qfileInfo.group().toStdString();

            NodeTM* item = new NodeTM(fileinfo, parent->depth + 1, 0 );
            parent->children.push_back(item);
            //qDebug() << __PRETTY_FUNCTION__ << " Appended(dir)= " << childdir.path() << ", Depth=" << parent->depth + 1;;
            this->scanFileSystem(childdir, item);
        }
    } // for
}
