#include "GUI.h"

GUI::GUI(QWidget *parent) : QMainWindow(parent), ui( new Ui::GUI )
{
    ui->setupUi(this);
    QWidget::showFullScreen();
    QWidget::showMaximized();

    loadSetting();

    // Scene
    scene = new QGraphicsScene();
    scene->setSceneRect( 0, 0, treemapSetting->value( "width", 1000 ).toInt(), treemapSetting->value( "height", 1000 ).toInt() );
    scene->setBackgroundBrush(Qt::darkGray);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->view->setScene(scene);

    /*
     * Treemap /
     * Mapping
     */
    //m_treemap = Treemap::instance(scene);
     m_mapping = new Mapping(scene);
    //connect(m_mapping, SIGNAL(signal_RelavanceFeddback(const FileInfo&)), this, SLOT(slot_RelavanceFeddback(const FileInfo&)));


    // QueryProcessor
    m_queryProcessor = new QueryProcessor();

    m_tableModel = NULL;

    /*
    m_client = new Client();
    connect(m_client, SIGNAL(signal_lastMessageFromServer(vector<FileInfo> &fileInfoVector)),
            this, SLOT(slot_visualiseResults(vector<FileInfo> &fileInfoVector)));
    */

    //m_dataManager = new DataManager();
    //m_cacheManager= new CacheManager();
}


GUI::~GUI()
{
    delete m_queryProcessor;
    //delete m_mapping;
    //delete m_treemap;
    //delete m_dataManager;
    //delete m_cacheManager;
}

void GUI::search()
{
    ui->searchButton->setEnabled(false);

    /* QueryParser: query format:
    * {"key":"Apple","type":"","sizefrom":"","sizeto":"","datefrom":"","dateto":""}
    * Size Unit: "GB", "MB", "KB", "B"
    */
    QJsonObject json;
    json["key"] = ui->key->text();
    json["type"] = ui->type->text();
    json["sizefrom"] = ui->sizeFrom->text() + " " + ui->sizeFromUnit->currentText();
    json["sizeto"] = ui->sizeTo->text() + " " + ui->sizeToUnit->currentText();

    QJsonDocument doc(json);
    QByteArray bytes = doc.toJson();
    QString query(bytes);

    cout << "Send Query: " << query.toStdString() << endl;

    //return;

    /*
     * Send for query processing & get the results.
     */
    vector <FileInfoX> fileInfoVec = m_queryProcessor->searchQtStandalone(query.toStdString());


    #ifdef GUI_DEMO
    if (fileInfoVec.size() >= MAX_RESULTS_TO_DISPLAY)
        fileInfoVec.erase(fileInfoVec.begin() + MAX_RESULTS_TO_DISPLAY, fileInfoVec.end());
    #endif

    /*
     * Build the treemap.
     * Encode Glyph.
     * Create the table view.
     */
     //m_mapping->startMapping(fileInfoVec);

    if (m_tableModel)
        delete m_tableModel;
    m_tableModel = new TableModel(fileInfoVec);
    ui->tableView->setModel(m_tableModel);
    ui->tableView->setVisible(false);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setVisible(true);

    ui->searchButton->setEnabled(true);
    ui->trainButton->setEnabled(true);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Search & Train ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


void GUI::on_searchButton_clicked()
{
    this->search();
}



void GUI::on_trainButton_clicked()
{
    cout << __PRETTY_FUNCTION__ <<  endl;
    ui->trainButton->setEnabled(false);

    vector<FileInfoX> newFileInfoVec;
    if (m_tableModel)
        newFileInfoVec = m_tableModel->getData();

    #ifdef TEST_MAP
    cout << "The user's selection, begiginning of the list. " << endl;
    for(vector<FileInfoX>::iterator it = newFileInfoVec.begin(); it != newFileInfoVec.end(); ++it)
       cout << it->m_select << endl;
    cout << "The user's selection, end of list... " <<  "Now Training... " << endl;
    #endif
    //m_queryProcessor->processFeedback(newFileInfoVec);

    #ifdef TEST_MAP
    vector<FileInfoX> newFileInfoVec;
    if (m_tableModel)
        newFileInfoVec = m_tableModel->getData();

    cout << __PRETTY_FUNCTION__ << ": The user's selection, begiginning of the list. " << endl;
    for(vector<FileInfoX>::iterator it = newFileInfoVec.begin(); it != newFileInfoVec.end(); ++it)
       cout << it->m_select << endl;
    cout << "The user's selection, end of list." << endl;
    #endif
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Buttons: Signals-Slots ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


void GUI::on_openVisualMapping_triggered()
{
    m_mapping->show();
}


void GUI::on_dirButton_clicked()
{
#if 0
    QString dir;
    #ifdef Q_OS_WIN
    dir = QFileDialog::getExistingDirectory( this, tr("Open Directory"), "D:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    #endif

    #ifdef Q_OS_LINUX
    dir = QFileDialog::getExistingDirectory( this, tr("Open Directory"), "/home/saiful", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    #endif

    if ( !dir.isEmpty())
        ui->dir->setText( dir );
#endif
}


void GUI::on_actionSqlite_Browser_triggered()
{
#if 0
    #ifdef Q_OS_WIN
    QString bin( "D:/Dropbox/DPhil-Research/Code/Search-Project/Server/Tools/sqlitestudio-2.1.4.exe" );
    QStringList args( "D:/Dropbox/DPhil-Research/Code/Search-Project/Server/Database/crawler.db.sqlite" );
    #endif

    #ifdef Q_OS_LINUX
    QString bin( "/usr/bin/sqlitestudio" );
    QStringList args( "/media/Storage/Dropbox/DPhil-Research/Code/Search-Project/Server/Database/crawler.db.sqlite" );
    #endif

    process.start(bin, args);
#endif
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setting ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void GUI::loadSetting()
{
    treemapSetting = new QSettings( "TreemapSetting", "TreemapSetting" );

    #ifdef Q_OS_WIN
    ui->dir->setText(treemapSetting->value( "dir", "D:/" ).toString());
    #endif
    #ifdef Q_OS_UNIX
    //ui->dir->setText(treemapSetting->value( "dir", "/home/saiful" ).toString());
    #endif

}


void GUI::saveSetting()
{
    //treemapSetting->setValue("dir", ui->dir->text());
}


void GUI::on_treemapSetting_triggered()
{
    //m_treemap->show();
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TESTING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void GUI::on_actionExit_triggered()
{
    // Need to find a way to delete, so that ontologies saves.
}


void GUI::on_actionDataManager_triggered()
{
#if 0
    m_dataManager->show();
#endif
}

void GUI::on_actionCacheManager_triggered()
{
#if 0
    m_cacheManager->show();
#endif
}
