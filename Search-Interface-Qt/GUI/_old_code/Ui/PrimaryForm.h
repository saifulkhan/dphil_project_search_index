#ifndef PrimaryForm_H
#define PrimaryForm_H

#include <QWidget>
#include <QColorDialog>
#include "ui_PrimaryForm.h"
#include "../GUI/GlobalVariables.h"


class PrimaryForm :  public QWidget, private Ui::PrimaryForm
{
    Q_OBJECT

private:
    QColor _color;                // TODO: find a way to get rid of this.
    PrimaryProperty_S _pri;

protected slots:
    void on_colorButton_clicked();

public:
    explicit PrimaryForm (QWidget *parent = 0);
    ~PrimaryForm();
    void setProperty (const PrimaryProperty_S &);
    PrimaryProperty_S getProperty ();
};

#endif
