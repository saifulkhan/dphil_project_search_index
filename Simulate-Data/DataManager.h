#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDesktopWidget> // Dont know about this header file. Added to avoid Qt5 compilation error.
#include <QApplication>
#include <QSettings>
#include <QFileDialog>
#include <string>

#include "GenSimFiles.h"
#include "GenSystemStat.h"
#include "ui_DataManager.h"

class DataManager : public QDialog
{
    Q_OBJECT
private:
    Ui::DataManager* ui;

public:
    explicit DataManager(QDialog* parent = 0);
    ~DataManager();

private slots:
    void on_applyButton_clicked();
    void on_simRadioButton_clicked();
    void on_statRadioButton_clicked();
};


#endif // DATAMANAGER_H
