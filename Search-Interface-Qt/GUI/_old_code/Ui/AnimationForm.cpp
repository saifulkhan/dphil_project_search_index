#include "AnimationForm.h"
#include "TF/TransferFunction.h"

AnimationForm::AnimationForm (QWidget *parent) : QWidget(parent), ui (new Ui::AnimationForm)
{
    ui->setupUi (this);
}


AnimationForm::~AnimationForm ()
{

}


void AnimationForm:: setProperty (const Animation &an)
{
    _an = an;

    ui->propertyComboBox->setCurrentIndex (_an.antype);
    ui->startSpinBox->setValue(_an.start);
    ui->stopSpinBox->setValue(_an.stop);

    ui->durationSpinBox->setValue(_an.duration);

    // TODO: setup the graph - setupWinProperty (_an.tfVector)
}

Animation AnimationForm::getProperty ()
{
    _an.setType (ui->propertyComboBox->currentText() );
    _an.start = ui->startSpinBox->value();
    _an.stop = ui->stopSpinBox->value();
    _an.duration = ui->durationSpinBox->value();

    _an.points = ui->tf->getTransferFunction().size();
    _an.tfVector = ui->tf->getTransferFunction();

    return _an;
}
