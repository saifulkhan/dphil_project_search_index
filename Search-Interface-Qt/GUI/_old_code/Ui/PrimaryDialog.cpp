#include "PrimaryDialog.h"

PrimaryDialog::PrimaryDialog(QWidget *parent) : QWidget(parent)
{
    setupUi (this);

}

void PrimaryDialog::on_applyPushButton_clicked()
{
    _property = primaryProperty->getProperty ();

    qDebug() << "PrimaryDialog:: Emiting Signal... ";
    //qDebug() << _property;

    emit PrimaryDialog_Signal (_property);
}


void PrimaryDialog::on_okPushButton_clicked()
{
    on_applyPushButton_clicked ();
    this->close();
}


void PrimaryDialog::on_cancelPushButton_clicked()
{
    primaryProperty->setProperty (_property);   // Reset to old
    this->close();
}
