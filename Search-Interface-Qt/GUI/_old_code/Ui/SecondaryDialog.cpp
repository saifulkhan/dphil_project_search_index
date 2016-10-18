#include "SecondaryDialog.h"

SecondaryDialog::SecondaryDialog(QWidget *parent) : QWidget(parent), ui (new Ui::SecondaryDialog)
{
    ui->setupUi(this);

}


void SecondaryDialog::on_applyPushButton_clicked()
{
    _property = ui->secondaryForm->getProperty ();
    _anproperty = ui->animationForm->getProperty ();

    qDebug() << "SecondaryDialog:: Emiting Signal... ";

    emit SecondaryDialog_Signal (_property, _anproperty);
}


void SecondaryDialog::on_okPushButton_clicked()
{
    on_applyPushButton_clicked();

    this->close();
}


void SecondaryDialog::on_cancelPushButton_clicked()
{
    ui->secondaryForm->setProperty (_property);
    ui->animationForm->setProperty (_anproperty);

    this->close();
}
