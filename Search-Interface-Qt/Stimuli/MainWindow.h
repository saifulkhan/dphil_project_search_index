#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "ui_MainWindow.h"
#include "TestA.h"
#include "TestB.h"
#include "TestC.h"
#include "Global.h"
#include "../Common/Common.h"

namespace Stimuli
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        private:
            Ui::MainWindow *ui;
            TestA *testA;
            TestB *testB;
            TestC *testC;
            int trialNo;

            void startTrial();
            void addInstruction();

        public slots:
            void TestA_Slot ();
            void TestB_Slot ();
            void TestC_Slot ();

        private slots:
            void on_startTestButton_clicked();
            void on_idButton_clicked();
            void on_actionInstructions_triggered();
            void on_actionAbout_triggered();

    public:
            explicit MainWindow (QWidget *parent = 0);
            ~MainWindow ();
    };
}
#endif // MAINWINDOW_H
