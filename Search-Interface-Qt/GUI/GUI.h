#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QSettings>
#include <QProcess>
#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>
#include <FileInfo.h>
#include <QueryProcessor.h>

#include "ui_GUI.h"
#include "Table.h"

 #include "Mapping.h"

#define MAX_RESULTS_TO_DISPLAY 100000

using namespace std;

namespace Ui
{
    class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT

private:
    Ui::GUI*        ui;
    QGraphicsScene* scene;
    QProcess        process;
    QSettings*      treemapSetting;
    TableModel*     m_tableModel;
    QueryProcessor* m_queryProcessor;

    //Treemap*        m_treemap;
     Mapping*        m_mapping;
    //DataManager*    m_dataManager;
    //CacheManager*   m_cacheManager;

    void loadSetting();
    void saveSetting();
    void search();
    void server_independent_testing();

public:
    explicit GUI(QWidget *parent = 0);
    ~GUI();

signals:

private slots:
    // Receive Feedback from the Mapping
    void on_trainButton_clicked();

    // UI buttons / menues
    void on_searchButton_clicked();
    void on_treemapSetting_triggered();
    void on_openVisualMapping_triggered();
    void on_dirButton_clicked();
    void on_actionSqlite_Browser_triggered();
    void on_actionExit_triggered();
    void on_actionDataManager_triggered();
    void on_actionCacheManager_triggered();
};

#endif // GUI_H
