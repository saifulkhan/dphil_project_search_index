#include "TestA.h"

using namespace Stimuli;

TestA::TestA (int t, QWidget *parent) : trials(t), QWidget (parent), ui (new Ui::TestA)
{
    qDebug() << __PRETTY_FUNCTION__ << "Constructor.";

    ui->setupUi (this);
    this->setWindowState(Qt::WindowFullScreen);
    this->setCursor(Qt::BlankCursor);

    // Setup scenes, views and add the main Treemap
    sceneTm = new QGraphicsScene ();
    sceneTm->setSceneRect (0, 0, WIDTH, HEIGHT);
    ui->viewTm->setScene ( sceneTm);

    sceneTmFirst = new QGraphicsScene ();
    sceneTmFirst->setSceneRect (0, 0, GLYPH_SIZE, GLYPH_SIZE);
    ui->viewTmFirst->setScene (sceneTmFirst);

    sceneTmSecond = new QGraphicsScene ();
    sceneTmSecond->setSceneRect (0, 0, GLYPH_SIZE, GLYPH_SIZE);
    ui->viewTmSecond->setScene (sceneTmSecond);

    processEvent = false;
    timer = new QElapsedTimer ();
    trialNo = 0;

    // Random stuffs
    RandInt *randInt = new RandInt ();
    RandDraw *randDraw = new RandDraw (trials, TOTAL_TF);

    totalTrials = trials * TOTAL_TF;
    for (int i = 0; i < totalTrials; i++) {
        tFunctions.push_back(randDraw->draw());
        int temp1 = randInt->getRandInt(0, TOTAL_TREEMAPS - 1);  // Treemap image no should be 0,1, ... 19 (20-1).
        tMaps.push_back(temp1);

        int temp2;
        do {
            temp2 = randInt->getRandInt(0, TOTAL_TREEMAPS - 1);
        } while (temp2 == temp1);

        if (randInt->getRandInt(0, 1) == 0)
            tMapOptions.push_back(QPair <int, int> (temp1, temp2));
        else
            tMapOptions.push_back(QPair <int, int> (temp2, temp1));
    }

    // Result file
    outFile = new QFile ("TestResult.csv");
    outFile->open (QIODevice::WriteOnly | QIODevice::Append);
    tStream = new QTextStream(outFile);

    if (trials > 1){
        *tStream << endl << "ID" << "," << "Trial No." << "," << "TF" << "," << "TM(Centre)" << "," << "TM(First)" << "," <<
                    "TM(Second)" << "," << "Answer(Key)" << "," << "RT(msec)" << "," << "Correct" << endl;
    }
}


TestA::~TestA()
{
    qDebug() << __PRETTY_FUNCTION__ << "Destructor.";
    delete tStream;
    outFile->close();
    delete outFile;
}


void TestA::startTrial ()
{
    if (trialNo < totalTrials) {
        addWhiteNoise();
        qDebug() << __PRETTY_FUNCTION__ << "Trial No= " << trialNo;
        addStimulis();
    } else {
        emit TestA_Signal ();
    }
}


void TestA::addStimulis()
{
    sceneTm->clear();
    sceneTm->addPixmap (QPixmap (QString (":Resources/Treemap/Treemap.png")));

    // Add sub treemap under glyph
    QPixmap pix = QPixmap(":Resources/Treemap/T" + QString::number(tMaps[trialNo]) + ".png");
    QGraphicsPixmapItem *tm = sceneTm->addPixmap(pix);
    tm->setPos(sceneTm->sceneRect().center().x() - GLYPH_SIZE / 2, sceneTm->sceneRect().center().y() - GLYPH_SIZE / 2);
    qDebug() << __PRETTY_FUNCTION__ << "TM added, TM.No#" << tMaps[trialNo];

    // Add glyph on treemap
    Animation an;
    an.setType ("opacity");
    an.start = 1;
    an.stop = 0;
    an.duration = 1500; // ms
    an.tfVector = getTF (tFunctions[trialNo]);
    Secondary sec;
    sec.setType ("Circle");
    sec.size = QSizeF (30, 30);
    sec.color = QColor("#2DB9D2");     // Paleblue: QColor::QColor("#A4FFFF");
    sec.pen = 1;
    Glyph *glyph = instance (sec, an);
    glyph->setPos(sceneTm->sceneRect().center());
    sceneTm->addItem (glyph);
    qDebug() << __PRETTY_FUNCTION__ << "Glyph added, TF.No#" << tFunctions[trialNo] << an;

    // options
    sceneTmFirst->clear();
    pix = QPixmap(":Resources/Treemap/T" + QString::number(tMapOptions[trialNo].first) + ".png");
    tm = sceneTmFirst->addPixmap(pix);

    sceneTmSecond->clear();
    pix = QPixmap(":Resources/Treemap/T" + QString::number(tMapOptions[trialNo].second) + ".png");
    tm = sceneTmSecond->addPixmap(pix);
    qDebug() << __PRETTY_FUNCTION__ << "TM Options added, TM.No#" << tMapOptions[trialNo].first << ", " << tMapOptions[trialNo].second;

    timer->restart();
}


void TestA::keyPressEvent(QKeyEvent* event)
{
    if (processEvent && (event->key() == Qt::Key_D || event->key() == Qt::Key_K)) {
        qDebug () << __PRETTY_FUNCTION__ << "Pressed: " << event->text();

        Qt::Key correctKey;
        if (tMaps[trialNo] == tMapOptions[trialNo].first)
            correctKey = Qt::Key_D;
        else
            correctKey = Qt::Key_K;

        bool answer;
        if (event->key() == correctKey)
            answer = true;
        else
            answer = false;
        if (trials > 1) {
        *tStream << id << "," << trialNo << "," << tFunctions[trialNo] << "," << tMaps[trialNo] << "," << tMapOptions[trialNo].first << "," <<
                    tMapOptions[trialNo].second << "," << event->text() << "," << timer->elapsed() << "," << answer << endl;
        }

        trialNo ++;
        startTrial ();

    } else {
        event->ignore();
        return;
    }
}


void TestA::addWhiteNoise ()
{
    processEvent = false;
    ui->viewTm->setVisible(false);
    ui->viewTmFirst->setVisible(false);
    ui->viewTmSecond->setVisible(false);

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

    ui->viewTm->setVisible(true);
    ui->viewTmFirst->setVisible(true);
    ui->viewTmSecond->setVisible(true);
    processEvent = true;
}
