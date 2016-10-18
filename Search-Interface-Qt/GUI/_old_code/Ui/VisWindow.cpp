#include "VisWindow.h"

#include "Glyph/Secondary.h"
#include "Glyph/Animation.h"
#include "Glyph/PrimaryGlyph.h"
#include "Glyph/SecondaryGlyph.h"

#include "FSGlyph/FSMapping.h"


using namespace std;

VisWindow::VisWindow(QWidget *parent) : QMainWindow (parent), ui (new Ui::VisWindowForm)
{
    ui->setupUi (this);
    treemap = NULL;
    crawler = NULL;
    //_query = NULL;

    //QWidget::setGeometry(QApplication::desktop()->availableGeometry());

    _createSceneView ();

    //ui->toolBox->insertItem(0, ui->searchButton, "Search");

    treemap = new  TreemapNS::TreemapInterface(_scene);
    //ui->dockWidget->setWidget(treemap);
    ui->toolBox->insertItem(1, treemap, "Treemap");

    QVector <QFileInfo> fileInfoVec;
    FSMapping *mapping = new FSMapping( fileInfoVec, _scene);
    ui->toolBox->insertItem(2, mapping, "Mapping Glyphs");




    _priDialog = new  PrimaryDialog ();
    connect (_priDialog, SIGNAL (PrimaryDialog_Signal (PrimaryProperty_S) ), this, SLOT (PrimaryDialog_Slot (PrimaryProperty_S)) );

    _secDialog = new  SecondaryDialog ();
    connect (_secDialog, SIGNAL (SecondaryDialog_Signal (Secondary, Animation) ), this, SLOT (SecondaryDialog_Slot (Secondary, Animation) ) );

    _visualMappingDialog = new VisualMapping ();
    connect (_visualMappingDialog, SIGNAL ( VisualMapping_Signal () ), this, SLOT ( VisualMapping_Slot () ) );
}


VisWindow::~VisWindow()
{
    //   delete
    delete crawler;
    delete treemap;
}


// Receive the property and change the properties of all dots.
void VisWindow:: PrimaryDialog_Slot (PrimaryProperty_S p)
{
    for (int i = 0; i < _fileList.size(); i++)
    {
        p.axis = _fileList.at(i).axis;
        _priProperty[i] = p;
    }

    qDebug() << "VisWindow:: PrimaryProperty signal received: " << p;

    _redrawGlyphs();
}


// Receive the property and change the properties of all Secondaries.
void VisWindow:: SecondaryDialog_Slot (Secondary sp, Animation an)
{
    for (int i = 0; i < _fileList.size(); i++)
    {
        sp.axis = _fileList.at(i).axis;
        _secProperty[i] = sp;
        _secAnProperty[i] = an;
    }

    qDebug() << "VisWindow:: SecondaryProperty signal received: " << sp << an;

    _redrawGlyphs();
}



void VisWindow::on_searchButton_clicked()
{
//    if (!rootTreemapItem) {
//        qDebug() << __PRETTY_FUNCTION__ << " Draw the Treemap first. ";
//        return;
//    }

    _buffer = new Buffer ();
    SearchInterface *searchInterface = new SearchInterface(_buffer);
    searchInterface->show();

    qDebug() << __PRETTY_FUNCTION__ << "After _query->show () ";
    _searchResult = new SearchResult (_scene, searchInterface->result(), _buffer);
    _searchResult->start();
     qDebug() << __PRETTY_FUNCTION__ << "After _searchResult->run() ";
    //ui->searchKey->setText (_query->getQuery () );
}


void VisWindow:: _openData ()
{

    QFileDialog *dialog = new QFileDialog;
    QString url = dialog->getOpenFileName (this, tr("Open Data"), ":/Resources/", "Data files (*.txt)" );
    if (url.isNull () )
    {
        return;
    }
    _data = new Data (url);

    TableModel *model = new TableModel (_data->getFileList());

    // TODO: tableView => QTableView is deleted from the UI, was in the tab
    //ui->tableView->setModel (model);


    // Clear the vectors before loading new set of datas. Otherwise it will keep appending ??
    _fileList.clear();
    _fileList = _data->getFileList ();

    _mapProperties ();
}


void VisWindow::_mapProperties ()
{
    qDebug () << "VisWindow::_mapProperties: Mapping ...";

    _priProperty.clear();
    _secProperty.clear();
    _secAnProperty.clear();

    for (int i = 0; i < _fileList.size(); i++)
    {
        PrimaryProperty_S pri = _visualMappingDialog->getPriProperty (_fileList.at(i));
        Secondary sec = _visualMappingDialog->getSecProperty (_fileList.at(i));
        Animation an = _visualMappingDialog->getAnProperty (_fileList.at(i));

        qDebug() << "Mapped properties: " << endl << pri << sec << an;

        _priProperty.push_back ( pri );
        _priProperty[i].axis = _fileList.at(i).axis;
        _secProperty.push_back ( sec );
        _secProperty[i].axis = _fileList.at(i).axis;
        _secAnProperty.push_back ( an );
    }

    _redrawGlyphs();
}


/// Mapping window changed the property.

void VisWindow:: VisualMapping_Slot ()
{
    _mapProperties ();
}


/// Create a single glyph and return the pointer.

Glyph* VisWindow::_createGlyph (PrimaryProperty_S sp)
{
    return new PrimaryGlyph (sp);
}


Glyph* VisWindow::_createGlyph (Secondary sec, Animation an)
{
    Glyph *glyph;
    glyph = instance (sec, an);

    return glyph;
}


/// Craeate a vector of pri glyphs

void VisWindow::_createPriGlyphs ()
{
    _priGlyphVec.clear();
    for (int i = 0; i < _priProperty.size(); i++)
    {
        _priGlyphVec.push_back ( _createGlyph (_priProperty[i]) );
    }
}


void VisWindow::_createSecGlyphs ()
{
    _secGlyphVec.clear();
    for (int i = 0; i < _secProperty.size(); i++)
    {
        _secGlyphVec.push_back ( _createGlyph (_secProperty[i], _secAnProperty[i]) );
    }
}


/// Pass a vector, which adds glyphs to scene
void VisWindow:: _addtoScene (vector <Glyph *> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        _scene->addItem (vec[i]);
    }
}


// Remove from scene and Clear the vector
void VisWindow::_deleteGlyphs (vector <Glyph *> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        _scene->removeItem (vec[i]);
    }
    vec.clear();
}


// Delete from scene, create glyphs and draw them
void VisWindow::_redrawGlyphs()
{
    _deleteGlyphs (_priGlyphVec);
    _deleteGlyphs (_secGlyphVec);

    _createPriGlyphs ();
    _addtoScene (_priGlyphVec);

    _createSecGlyphs ();
    _addtoScene (_secGlyphVec);
}


/// Show / hide
void VisWindow:: _showGlyph (bool flag, vector <Glyph *> &vec)
{
    if (flag)
    {
        for (int i = 0; i < vec.size(); i++)
            vec[i]->show();
    }
    else
    {
        for (int i = 0; i < vec.size(); i++)
            vec[i]->hide();
    }
}


/// Animation methods
void VisWindow::_animate (bool flag, vector <Glyph *> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        //vec[i]->animate (flag);
    }
}


void VisWindow::_createSceneView ()
{
    QSettings settings( "TreemapSetting", "treemapSetting" );

    // Create QGraphicsScene and QGraphicsView
    _scene = new QGraphicsScene (this);
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    _scene->setSceneRect (0, 0, settings.value( "width" ).toInt(), settings.value( "height" ).toInt());
    ui->graphicsView->setScene(_scene);
    //ui->graphicsView->resize( _scene->sceneRect().width(), _scene->sceneRect().height() );
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QBrush(VISWINDOW_COLOR));
}


///////////////////////////////////////////////////////////////////////////////
//
//  Dock
//
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Menu

// Open treemap & setup treemap
void VisWindow::on_openTreemap_triggered()
{
    if (!treemap)
         treemap = new TreemapNS::TreemapInterface( _scene );
    treemap->buildTreemap();
}

void VisWindow::on_treemapSetting_triggered()
{
    if (!treemap)
         treemap = new TreemapNS::TreemapInterface( _scene );
     treemap->show();   // create with the existing setting; and then show the interface to change settings.
}


void VisWindow::on_openData_triggered()
{
    _openData ();
}


void VisWindow::on_saveView_triggered()
{
    QFileDialog *dialog = new QFileDialog;
    QString url = dialog->getSaveFileName (this, "Enter File Name", ":/Resources/", tr("Export Files (*.dat)"));
    if (url.isNull () )
    {
       return;
    }

    OpenSave os (url);
    os.saveSetting (_priProperty, _secProperty, _secAnProperty);
}

void VisWindow::on_openView_triggered()
{

    QFileDialog *dialog = new QFileDialog;
    QString url = dialog->getOpenFileName (this, "Enter File Name", ":/Resources/settings/", tr("Export Files (*.dat)"));
    if (url.isNull () )
        return;
    OpenSave os (url);
    os.openSetting (_priProperty, _secProperty, _secAnProperty);

    _redrawGlyphs();
}


void VisWindow::on_actionExit_triggered()
{
    this->close ();
}


/// Setting

void VisWindow::on_openPriProperty_triggered()
{
    _priDialog->show();
}

void VisWindow::on_openSecProperty_triggered()
{
    _secDialog->show();
}

void VisWindow::on_openVisualMapping_triggered()
{
    _visualMappingDialog->show();
}

void VisWindow::on_crawlerSetting_triggered()
{
    if ( !crawler )
        crawler = new Crawler();
    crawler->show();
}

void VisWindow::on_actionIndexBrowser_triggered()
{
    QStringList env = QProcess::systemEnvironment();
    QString program = "java";
    QStringList arguments;
    arguments << "-jar" << "/home/saiful/D/Dropbox/DPhil-Research/Release-and-Tools/Tools/lukeall-3.5.0.jar";
    QProcess *process = new QProcess(qApp);
    process->setEnvironment(env);
    process->start(program, arguments);

}

void VisWindow::on_actionSqlitesStudio_triggered()
{
    QStringList env = QProcess::systemEnvironment();
    QString program = "/home/saiful/D/Dropbox/DPhil-Research/Release-and-Tools/Tools/sqlitestudio";
    QStringList arguments;
    QProcess *process = new QProcess(qApp);
    process->setEnvironment(env);
    process->start(program, arguments);
}
