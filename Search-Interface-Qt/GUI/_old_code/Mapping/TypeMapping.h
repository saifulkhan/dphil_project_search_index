#ifndef TYPEMAPPING_H
#define TYPEMAPPING_H

#include "ui_TypeMappingForm.h"

#include <QComboBox>
#include <QWidget>
#include <QMap>
#include <QDebug>


class TypeMapping : public QWidget
{
    Q_OBJECT

private:
    Ui::TypeMappingForm *ui;
    QStandardItemModel *_model;
    QMap <FileType_E, Properties_S> _typeMap;

    void _updateProperty ();

public slots:

public:
    explicit TypeMapping (QWidget *parent = 0);
    ~TypeMapping ();

    void setProperty ( const QMap <FileType_E, Properties_S> &);
    QMap <FileType_E, Properties_S> getProperty ();
};


#endif // TYPEMAPPING_H
