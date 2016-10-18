#ifndef TESTA_H
#define TESTA_H

#include <QWidget>
#include <QElapsedTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include "ui_TestA.h"

#include "Global.h"

#include "../Common/Common.h"
#include "../GUI/Glyph/Animation.h"
#include "../GUI/Glyph/Secondary.h"
#include "../GUI/Glyph/SecondaryGlyph.h"


namespace Stimuli
{
    /// Test A
    #define WIDTH 400
    #define HEIGHT 400
    #define GLYPH_SIZE 60
    #define TOTAL_TREEMAPS 20

    class TestA : public QWidget
    {
        Q_OBJECT

    private:
        Ui::TestA *ui;
        QGraphicsScene *sceneTm;
        QGraphicsScene *sceneTmFirst;
        QGraphicsScene *sceneTmSecond;
        int trials;
        int totalTrials;
        QVector <int> tFunctions;
        QVector <int> tMaps;
        QVector <QPair <int, int> > tMapOptions;

        bool processEvent;
        QElapsedTimer *timer;

        // Variables to record in table
        QFile *outFile;
        QTextStream *tStream;
        int trialNo;

        // Methods
        void addStimulis();
        void addWhiteNoise();

    protected:
        void keyPressEvent(QKeyEvent *);

    public:
        explicit TestA(int trials, QWidget *parent = 0);
        ~TestA();
        void startTrial();

    signals:
        void TestA_Signal ();

    };

}
#endif // TestA_H
