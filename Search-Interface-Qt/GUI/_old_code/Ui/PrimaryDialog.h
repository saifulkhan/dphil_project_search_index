#ifndef PRIMARYDIALOG_H
#define PRIMARYDIALOG_H

#include "ui_PrimaryDialog.h"

class PrimaryDialog : public QWidget, private Ui::PrimaryDialog
{
    Q_OBJECT

public:
    PrimaryProperty_S _property;

signals:
    void PrimaryDialog_Signal (PrimaryProperty_S);

private slots:
    void on_cancelPushButton_clicked();
    void on_applyPushButton_clicked();
    void on_okPushButton_clicked();

public:
    explicit PrimaryDialog (QWidget *parent = 0);
};

#endif
