#include "TestC.h"

using namespace Stimuli;

TestC::TestC(int t, bool a, QWidget *parent) : trials (t),  noanimation( a ), QWidget(parent), ui (new Ui::TestC)
{
    qDebug() << __PRETTY_FUNCTION__ << "Constructor.";
    ui->setupUi (this);
    this->setWindowState(Qt::WindowFullScreen);
    this->setCursor(Qt::BlankCursor);

    processEvent = false;
    timer = new QElapsedTimer ();
    trialNo = 0;

    sceneFirst = new QGraphicsScene();
    ui->viewFirst->setScene(sceneFirst);
    sceneSecond = new QGraphicsScene();
    ui->viewSecond->setScene(sceneSecond);

    // Random stuffs
    RandInt *randInt = new RandInt ();
    RandDraw *randDraw = new RandDraw (trials, TOTAL_DELTAS);

    totalTrials = trials * TOTAL_DELTAS;

    for (int i = 0; i < totalTrials; i++) {
        //deltas.push_back((randDraw->draw() * 2) + 2); // delta = 2, 4, 6, ..., 30
        deltas.push_back(randDraw->draw() + 1); // delta = 1, 2, 3, ..., 20
    }

    for (int i = 0; i < totalTrials; i++) {
        int arch1;
        int arch2;
        do {
            arch1 = randInt->getRandInt(10, 350 - deltas[i]); // Lenghth of the Arch: min= 10 deg and max=350 deg.
            arch2 = arch1 + deltas[i];
        } while (arch1 == 90 ||arch1 == 180 || arch1 == 270 || arch2 == 90 || arch2 == 180 || arch1 == 270);

        if (randInt->getRandInt(0, 1) == 0)
            screens.push_back(QPair <int, int> (arch1, arch2));
        else
            screens.push_back(QPair <int, int> (arch2, arch1));
    }

    // Result file
    outFile = new QFile ("TestResult.csv");
    outFile->open (QIODevice::WriteOnly | QIODevice::Append);
    tStream = new QTextStream(outFile);
    if (trials > 1) {
        *tStream << endl << "ID" << "," << "Trial No." << "," << "First" << "," << "Second" << "," <<
                    "Delta" << "," << "Answer(Key)" << "," << "RT(msec)" << "," << "Correct" << endl;
    }
}


TestC::~TestC()
{
    qDebug() << __PRETTY_FUNCTION__ << "Destructor.";
    delete tStream;
    outFile->close();
    delete outFile;
}


void TestC::startTrial ()
{
    if (trialNo < totalTrials) {
          addWhiteNoise();
          qDebug() << __PRETTY_FUNCTION__ << "Trial No= " << trialNo;
          addStimulis();        
      } else {
          emit TestC_Signal();
      }
}


void TestC::addStimulis()
{
    sceneFirst->clear();
    sceneSecond->clear();
    //timer->restart();

    Secondary sec;
    sec.setType("Pie");
    sec.size = QSizeF (60, 60);
    sec.color = QColor("#2DB9D2"); //QColor::QColor("#A4FFFF");
    sec.pen = 1;

    Animation an;
    an.setType ("rotationZ");

    if (noanimation)
        an.start = screens[trialNo].first; // will not animate, start = final value.
    else
        an.start = 10;

    an.stop = screens[trialNo].first;
    an.duration = 1500;
    an.tfVector = getTF (14);
    an.points = an.tfVector.size();

    Glyph *g1 = instance (sec, an);
    sceneFirst->addItem (g1);

    // Second
    if (noanimation)
        an.start = screens[trialNo].second; // will not animate, start = final value.
    else
        an.start = 10;

    an.stop = screens[trialNo].second;

    g1 = instance (sec, an);
    sceneSecond->addItem (g1);

    qDebug() << __PRETTY_FUNCTION__ << an;
    qDebug() << __PRETTY_FUNCTION__ << "Arch lengths (degree)= " << screens[trialNo].first << ", " << screens[trialNo].second <<
                " Delta= " << deltas[trialNo];

    timer->restart();
}


void TestC::keyPressEvent(QKeyEvent* event)
{
    if (processEvent && (event->key() == Qt::Key_D || event->key() == Qt::Key_K)) {
        qDebug () << __PRETTY_FUNCTION__ << "Pressed: " << event->text();

        Qt::Key correctKey;
        if (screens[trialNo].first > screens[trialNo].second)
            correctKey = Qt::Key_D;
        else
            correctKey = Qt::Key_K;

        bool answer;
        if (event->key() == correctKey)
            answer = true;
        else
            answer = false;

        if (trials > 1) {
            *tStream << id << "," << trialNo << "," << screens[trialNo].first << "," << screens[trialNo].second << "," <<
                        deltas[trialNo] << "," << event->text() << "," << timer->elapsed() << "," << answer << endl;
        }
        trialNo ++;
        startTrial ();

    } else {
        event->ignore();
        return;
    }
}


void TestC::addWhiteNoise()
{
    processEvent = false;
    ui->viewFirst->setVisible(false);
    ui->viewSecond->setVisible(false);

    QPalette p(palette());
    // Set background colour to black
    p.setBrush(QPalette::Background, QBrush(QImage(":Resources/White-noise.jpg")));
    setPalette(p);

    QTime dieTime = QTime::currentTime().addMSecs(WN_DELAY);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    if ((trialNo != 0) && (trialNo % 50 == 0))
        QMessageBox::information(this, "Break", "Please take a break. Press OK to resume.", QMessageBox::Ok);

    p.setColor(QPalette::Background, Qt::lightGray);
    setPalette(p);

    ui->viewFirst->setVisible(true);
    ui->viewSecond->setVisible(true);
    processEvent = true;
}
