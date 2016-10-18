#include "TestB.h"

using namespace Stimuli;

TestB::TestB(int t, QWidget *parent) : trials(t), QWidget(parent), ui (new Ui::TestB)
{
    qDebug() << __PRETTY_FUNCTION__ << "Constructor.";

    ui->setupUi (this);
    this->setWindowState(Qt::WindowFullScreen);
    this->setCursor(Qt::BlankCursor);

    sceneFirst = new QGraphicsScene ();
    ui->viewFirst->setScene(sceneFirst);
    sceneSecond = new QGraphicsScene ();
    ui->viewSecond->setScene(sceneSecond);

    processEvent = false;
    timer = new QElapsedTimer ();
    trialNo = 0;


    // Random stuffs
    RandInt *randInt = new RandInt ();
    RandDraw *randDraw = new RandDraw (trials, TOTAL_TF);

    totalTrials = trials * TOTAL_TF;
    for (int i = 0; i < totalTrials; i++) {
        tFunctions.push_back(randDraw->draw());

        int temp1 = randInt->getRandInt(0, 5) * 5 + 15;  // No. 15, 20, ..., 40 px.
        int temp2;
        do {
            temp2 = randInt->getRandInt(0, 5) * 5 + 15;
        } while (temp2 == temp1);
           screens.push_back(QPair <int, int> (temp1, temp2));
    }

    // Result file
    outFile = new QFile ("TestResult.csv");
    outFile->open (QIODevice::WriteOnly | QIODevice::Append);
    tStream = new QTextStream(outFile);
    if (trials > 1) {
        *tStream << endl << "ID" << "," << "Trial No." << "," << "TF" << "," << "First" << "," << "Second" << "," <<
                    "Answer(Key)" << "," << "RT(msec)" << "," << "Correct" << endl;
    }
}


TestB::~TestB ()
{
    qDebug() << __PRETTY_FUNCTION__ << "Destructor.";
    delete tStream;
    outFile->close();
    delete outFile;
}


void TestB::startTrial()
{
    if (trialNo < totalTrials) {
           addWhiteNoise();
           qDebug() << __PRETTY_FUNCTION__ << "Trial No= " << trialNo;
           addStimulis();
       } else {
           emit TestB_Signal();
       }
}



void TestB::addStimulis()
{
    sceneFirst->clear();
    sceneSecond->clear();

    Secondary sec;
    sec.setType("Circle");
    sec.color = QColor("#2DB9D2"); //QColor::QColor("#A4FFFF");
    sec.pen = 1;
    sec.size = QSizeF (screens[trialNo].first, screens[trialNo].first);

    Animation an;
    an.setType ("scale");
    an.start = 0;
    an.stop = 1,
    an.duration = 1500;
    an.tfVector = getTF (tFunctions[trialNo]);
    an.points = an.tfVector.size();

    Glyph *g1 = instance (sec, an);
    sceneFirst->addItem (g1);

    // Second
    sec.size = QSizeF (screens[trialNo].second, screens[trialNo].second);
    Glyph *g2 = instance (sec, an);
    sceneSecond->addItem(g2);

    qDebug() << __PRETTY_FUNCTION__ << screens[trialNo] ;

    timer->restart();
}


void TestB::keyPressEvent(QKeyEvent* event)
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
            *tStream << id << "," << trialNo << "," << tFunctions[trialNo] << "," << screens[trialNo].first << "," << screens[trialNo].second << "," <<
                        event->text() << "," << timer->elapsed() << "," << answer << endl;
        }
        trialNo ++;
        startTrial ();

    } else {
        event->ignore();
        return;
    }
}


void TestB::addWhiteNoise()
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
