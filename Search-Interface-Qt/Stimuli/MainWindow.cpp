#include "MainWindow.h"
#include <QDebug>
#include <QMessageBox>

using namespace Stimuli;

MainWindow::MainWindow (QWidget *parent) : QMainWindow (parent), ui (new Ui::MainWindow)

{
    ui->setupUi (this);

}


MainWindow::~MainWindow()
{    
}


void Stimuli::MainWindow::on_startTestButton_clicked()
{
    ui->startTestButton->setEnabled (false);
    ui->exp3CheckBox->setEnabled( false );

    trialNo = 0;

    // Added this to do test-3 without animation.
    if ( ui->exp3CheckBox->isChecked() ) {
        trialNo = 4;
    }
    startTrial();
}


void MainWindow::startTrial()
{
    addInstruction();

    switch (trialNo) {
    /// Test A
    case 0:
        qDebug() << __PRETTY_FUNCTION__ << "Start Test A (Training: Experiment 1).";
        QMessageBox::information(this, "Training: Experiment 1", "Press OK to start the training.", QMessageBox::Ok);
        testA = new TestA (TRAINING_TRIAL);
        connect (testA, SIGNAL (TestA_Signal () ), this, SLOT (TestA_Slot ()) );
        testA->show();
        testA->startTrial();
        break;

    case 1:
        qDebug() << __PRETTY_FUNCTION__ << "Start Test A." << endl;
        QMessageBox::information(this, "Test: Experiment 1", "Training over. Press OK to start the test.", QMessageBox::Ok);
        testA = new TestA (TEST_TRIAL);
        connect (testA, SIGNAL (TestA_Signal () ), this, SLOT (TestA_Slot ()) );
        testA->show();
        testA->startTrial();
        break;


    /// Test B
    case 2:
        qDebug() << __PRETTY_FUNCTION__ << "Start Test B (Training: Experiment 2).";
        QMessageBox::information(this, "Training: Experiment 2", "Experiment 1 is complete.  Take a short break and press OK when you have read the instructions and are ready to continue with training for Experiment 2.", QMessageBox::Ok);
        testB = new TestB (TRAINING_TRIAL);
        connect (testB, SIGNAL (TestB_Signal () ), this, SLOT (TestB_Slot ()) );
        testB->show();
        testB->startTrial();
        break;

    case 3:
        qDebug() << __PRETTY_FUNCTION__ << "Start Test B." << endl;
        QMessageBox::information(this, "Test: Experiment 2", "Training over. Press OK to start the test.", QMessageBox::Ok);
        testB = new TestB (TEST_TRIAL);
        connect (testB, SIGNAL (TestB_Signal () ), this, SLOT (TestB_Slot ()) );
        testB->show();
        testB->startTrial();
        break;


    /// Test C
    case 4:
        qDebug() << __PRETTY_FUNCTION__ << "Start Test C (Training).";
        QMessageBox::information(this, "Training: Experiment 3", "Experiment 2 is complete.  Take a short break and press OK when you have read the instructions and are ready to continue with training for Experiment 3.", QMessageBox::Ok);
        testC = new TestC( TRAINING_TRIAL, ui->exp3CheckBox->isChecked() );
        connect (testC, SIGNAL (TestC_Signal () ), this, SLOT (TestC_Slot ()) );
        testC->show();
        testC->startTrial();
        break;

    case 5:
        qDebug() << __PRETTY_FUNCTION__ << "Start Test C." << endl;
        QMessageBox::information(this, "Test: Experiment 3", "Training over. Press OK to start the test.", QMessageBox::Ok);
        testC = new TestC( TEST_TRIAL, ui->exp3CheckBox->isChecked() );
        connect (testC, SIGNAL (TestC_Signal () ), this, SLOT (TestC_Slot ()) );
        testC->show();
        testC->startTrial();
        break;

    /// Complete
    default:
        QMessageBox::information(this, "Complete", "Tests are complete. Thank you.", QMessageBox::Ok);
        qDebug() << __PRETTY_FUNCTION__ << "All tests are complete.";
        break;
    }

    trialNo ++;
}


void MainWindow::TestA_Slot()
{
    qDebug() << __PRETTY_FUNCTION__ << "Test A is complete. Press OK continue.";
    delete testA;
    startTrial();
}


void MainWindow::TestB_Slot()
{
    qDebug() << "Test B is complete. Press OK continue.";
    delete testB;
    startTrial();
}


void MainWindow::TestC_Slot()
{
    qDebug() << "Test C is complete. Press OK continue.";
    delete testC;
    startTrial();
}


void MainWindow::on_idButton_clicked()
{
    id = ui->idLineEdit->text();

    ui->idButton->setEnabled(false);
    ui->idLineEdit->setEnabled(false);
}

void MainWindow::addInstruction()
{
     switch (trialNo) {
     case 0:
     case 1:
         ui->textBrowser->setText("This test will present you with 3 images; a larger one at the top, with 2 smaller ones below. One of these smaller images will be the same as the image at the centre of the larger image, and your task is to identify which one matches.  Make your selection using the keyboard, hitting the `D` key for the left-hand image, and the `K` key for the right hand image. Please make your choice as quickly as possible, but please  try to be as accurate as possible.");
         ui->textBrowser->setFontPointSize(11);
         ui->textBrowser->setFontWeight(QFont::Bold);
         break;

     case 2:
     case 3:
         ui->textBrowser->setText("This test will present you with 2 images side-by-side.  These images will consist of an animated circle, and your task is to identify which of the two circles is larger.  Make your selection using the keyboard, hitting the 'D' key for the left-hand image, and the 'K' key for the right hand image. Please make your choice as quickly as possible, but please try to be as accurate as possible. You will now be presented with a brief practice session. Hit the OK button to begin.");
         ui->textBrowser->setFontPointSize(11);
         ui->textBrowser->setFontWeight(QFont::Bold);
         break;

     case 4:
     case 5:
         ui->textBrowser->setText("This experiment will present you with 2 images side-by-side.  Here, you will see a circle on the screen.  A line will move around the outside of of this circle, with one of these lines going further around.  Your task is to identify which of the two lines moves further.  Make your selection using the keyboard, hitting the 'D' key for the left-hand image, and the 'K' key for the right hand image. Please make your choice as quickly as possible, but please try to be as accurate as possible.");
         ui->textBrowser->setFontPointSize(11);
         ui->textBrowser->setFontWeight(QFont::Bold);
         break;

     default:
         ui->textBrowser->setText("Tests are complete. Thank you.");
         ui->textBrowser->setFontPointSize(11);
         ui->textBrowser->setFontWeight(QFont::Bold);
         break;
     }

}

void MainWindow::on_actionInstructions_triggered()
{

}


void Stimuli::MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about (this, "Psychology Experiment", "Copyright (c) 2013 by Saiful Khan, Department of Engineering Science, University of Oxford. Email: saiful.khan@eng.ox.ac.uk");
}
