#ifndef TESTC_H
#define TESTC_H

#include <QWidget>
#include <QElapsedTimer>
#include <QMessageBox>>
#include "ui_TestC.h"

#include "Global.h"

#include "../Common/Common.h"
#include "../GUI/Glyph/Animation.h"
#include "../GUI/Glyph/Secondary.h"
#include "../GUI/Glyph/SecondaryGlyph.h"


namespace Stimuli
{
    /// Test C
    #define TOTAL_DELTAS 20

    class TestC : public QWidget
    {
        Q_OBJECT

    private:
        Ui::TestC *ui;
        QGraphicsScene *sceneFirst;
        QGraphicsScene *sceneSecond;
        int trials;
        int totalTrials;
        QVector <int> deltas;
        QVector <QPair <int, int> > screens;

        bool processEvent;
        QElapsedTimer *timer;

        // Variables to record in table
        QFile *outFile;
        QTextStream *tStream;
        int trialNo;

        // Animate or do not animate? This falg will decide.
        bool noanimation;

        // Methods
        void addStimulis();
        void addWhiteNoise();

    public:
        explicit TestC(int, bool noanimation = false, QWidget *parent = 0);
        ~TestC();
        void startTrial();

    signals:
        void TestC_Signal ();

    protected:
        void keyPressEvent(QKeyEvent *);
    };
}
#endif // TestC_H
