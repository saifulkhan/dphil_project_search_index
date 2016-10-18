#ifndef CHANNElMAPPING_H
#define CHANNELMAPPING_H

#include "ui_ChannelMappingForm.h"
#include <QtGui>
#include <QWidget>
#include <vector>

#include "GlobalVariables.h"
#include "Data/Data.h"
#include "ColourMap/ColourMap.h"

class VisWindow;

using namespace std;

class ChannelMapping : public QWidget, private Ui::ChannelMappingForm
{
    Q_OBJECT

private:
    QMap <VisAttr_E, FileAttr_E> _map;
    void _updateProperty ();

private slots:
    void on_pricolorCombobox_currentIndexChanged(int index);
    void on_seccolorCombobox_currentIndexChanged(int index);
    void on_secsizeCombobox_currentIndexChanged(int index);
    void on_secshapeCombobox_currentIndexChanged(int index);
    void on_anComboBox_currentIndexChanged(int index);

public:
    ChannelMapping (QWidget *parent = 0);
    ~ChannelMapping ();

    QMap <VisAttr_E, FileAttr_E> getProperty ();
    void setProperty (const QMap <VisAttr_E, FileAttr_E> &);


};

#endif // Mapping_H
