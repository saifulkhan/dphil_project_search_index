#include "PrimaryForm.h"

PrimaryForm::PrimaryForm (QWidget *parent) : QWidget(parent)
{
    setupUi (this);

    _color = DEF_COLOR;
}

PrimaryForm::~PrimaryForm()
{

}


void PrimaryForm::on_colorButton_clicked()
{
    QColorDialog *colorDialog = new QColorDialog (DEF_COLOR, this);
    _color = colorDialog->getColor ();

    if (! _color.isValid())
    {
        _color = DEF_COLOR;
    }

    _colorLabel->setText(_color.name());
    _colorLabel->setPalette(QPalette(_color));
    _colorLabel->setAutoFillBackground(true);
}

void PrimaryForm::setProperty (const PrimaryProperty_S &p)
{
    _pri = p;

    _sizeSpinBox->setValue(_pri.size);
    _colorLabel->setText(_pri.color.name());
    _colorLabel->setPalette(QPalette(_pri.color));
    _colorLabel->setAutoFillBackground(true);
}


PrimaryProperty_S PrimaryForm::getProperty ()
{
    _pri.size = _sizeSpinBox->value();
    _pri.color = _color;

    return _pri;
}

