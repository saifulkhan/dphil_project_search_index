#ifndef TESTB_H
#define TESTB_H

#include <QWidget>
#include <QElapsedTimer>
#include <QMessageBox>

#include "ui_TestB.h"

#include "Global.h"
#include "../Common/Common.h"
#include "../GUI/Glyph/Animation.h"
#include "../GUI/Glyph/Secondary.h"
#include "../GUI/Glyph/SecondaryGlyph.h"


namespace Stimuli
{
    class TestB : public QWidget
    {
        Q_OBJECT

    private:
        Ui::TestB *ui;
        QGraphicsScene *sceneFirst;
        QGraphicsScene *sceneSecond;
        int trials;
        int totalTrials;
        QVector <int> tFunctions;
        QVector <QPair <int, int> > screens;

        bool processEvent;
        QElapsedTimer *timer;

        // Variables to record in table
        QFile *outFile;
        QTextStream *tStream;
        int trialNo;


        // Methods
        void addStimulis();
        void addWhiteNoise();

    public:
        explicit TestB(int trials, QWidget *parent = 0);
        ~TestB();
        void startTrial();

    signals:
        void TestB_Signal ();

    protected:
        void keyPressEvent(QKeyEvent *);

    };
}
#endif // TestB_H
