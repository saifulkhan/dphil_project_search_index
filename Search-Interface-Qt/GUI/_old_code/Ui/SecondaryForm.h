#ifndef SecondaryForm_H
#define SecondaryForm_H

#include <QWidget>
#include <QColorDialog>>
#include "Glyph/Secondary.h"
#include "ui_SecondaryForm.h"


class SecondaryForm : public QWidget
{
    Q_OBJECT

private:
    Ui::SecondaryForm *ui;
    QColor _color;  // TODO: find a way to get rid of this.
    Secondary _sec;

protected slots:
    void on_colorButton_clicked();

public:
    SecondaryForm (QWidget *parent = 0);
    ~SecondaryForm ();
    void setProperty (const Secondary &);
    Secondary getProperty ();
};

#endif
