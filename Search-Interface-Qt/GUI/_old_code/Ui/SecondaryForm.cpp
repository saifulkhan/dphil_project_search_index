#include "SecondaryForm.h"
#include "GlobalVariables.h"

SecondaryForm::SecondaryForm (QWidget *parent) : QWidget(parent), ui (new Ui::SecondaryForm)
{
    ui->setupUi (this);
    setWindowTitle("Secondary Property");

    _color = DEF_COLOR;
}

SecondaryForm::~SecondaryForm ()
{

}


void SecondaryForm::on_colorButton_clicked()
{
    QColorDialog *colorDialog = new QColorDialog (DEF_COLOR, this);
    _color = colorDialog->getColor ();

    if (! _color.isValid())
    {
        _color = DEF_COLOR;
    }

    ui->_colorLabel->setText(_color.name());
    ui->_colorLabel->setPalette(QPalette(_color));
    ui->_colorLabel->setAutoFillBackground(true);
}


void SecondaryForm::setProperty (const Secondary &sp)
{
    _sec = sp;

   ui->glyphComboBox->setCurrentIndex (_sec.gtype);
   ui->_sizeSpinBox->setValue(_sec.size.height());
   ui->_colorLabel->setText(_sec.color.name());
   ui->_colorLabel->setPalette(QPalette(_sec.color));
   ui->_colorLabel->setAutoFillBackground(true);
}


Secondary SecondaryForm::getProperty ()
{
    _sec.setType (ui->glyphComboBox->currentText() ) ;

    _sec.size.setHeight(ui->_sizeSpinBox->value());
    _sec.size.setWidth (ui->_sizeSpinBox->value());
    _sec.color = _color;

    return _sec;
}
