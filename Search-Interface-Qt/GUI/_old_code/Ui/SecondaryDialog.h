#ifndef SECONDARYDIALOG_H
#define SECONDARYDIALOG_H

#include <QWidget>
#include "ui_SecondaryDialog.h"

class Secondary;
class Animation;

class SecondaryDialog : public QWidget
{
    Q_OBJECT

private:
    Ui::SecondaryDialog *ui;
    Secondary _property;
    Animation _anproperty;


signals:
    void SecondaryDialog_Signal (Secondary, Animation);
    

protected slots:
    void on_cancelPushButton_clicked();     // Cancel/Apply/OK button
    void on_applyPushButton_clicked();
    void on_okPushButton_clicked ();


public:
    explicit SecondaryDialog (QWidget *parent = 0);
};

#endif
