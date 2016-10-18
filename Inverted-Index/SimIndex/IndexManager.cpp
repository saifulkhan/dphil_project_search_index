#include "IndexManager.h"

IndexManager::IndexManager(QDialog* parent) : QDialog(parent), ui(new Ui::IndexManager) {
    ui->setupUi(this);
    ui->lineEdit_file->setText(FILE_SIM_DATA);
    m_index = SE::Index::instance();
    m_fileName = ui->lineEdit_file->text().toStdString();
}


IndexManager::~IndexManager() {
    delete m_index;
}


void IndexManager::on_applyButton_clicked() {
    if (ui->simRadioButton->isChecked()) {
        this->buildIndex();
    }
    else if (ui->crawlRadioButton->isChecked()) {
        // Crawl
        //Crawler crawler;
        //vector<FileInfo> fileInfovec = crawler.getFileList(m_crawlDiskPath);
        //for (FileInfo fileInfo : fileInfovec)
        //addToCache(fileInfo);
    }

    this->close();
}


/*
 * Open the simulated data file.
 * Read the datafile, create fileinfo and add to cache.
 */
void IndexManager::buildIndex() {
    int counter = 1;
    string line;
    string docId;
    string name;
    string type;
    string size;
    string dateTime;
    string path;
    string user;
    string group;

    m_index->open();

    /*
     * Count number of lines for the progress bar
     */
    ifstream fs(m_fileName);
    // new lines will be skipped unless we stop it from happening:
    fs.unsetf(std::ios_base::skipws);
    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = std::count(std::istream_iterator<char>(fs), std::istream_iterator<char>(), '\n');
    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(line_count);
    fs.close();

    /*
     * Read the simulated data file and create inverted index
     * TODO: This is inefficient, closing it and reopening it! Find a way to use fs agian.
     */
    ifstream fs1(m_fileName);

    while (getline(fs1, line)) {
        stringstream ss(line);
        getline(ss, docId, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, size, ',');
        getline(ss, dateTime, ',');
        getline(ss, path, ',');
        getline(ss, user, ',');
        getline(ss, group, ',');

        FileInfo fileInfo(stringToInt64(docId), name, type, stringToInt64(size), dateTime, "", "", user, group, path);

        m_index->add(fileInfo);

        ui->progressBar->setValue(++counter);
        ui->totalLabel->setText(QString::number(counter));

        #ifdef DBG_CACHE
        cout << __PRETTY_FUNCTION__ << fileInfo << endl;
        #endif
    }
    m_index->close();
    fs1.close();
    this->close();
}

void IndexManager::on_pushButton_selectFile_clicked() {
    m_fileName = QFileDialog::getOpenFileName(this,
                                              tr("Select simulated data file"), FILE_SIM_LOC, tr("Simulate data file (*.csv)"))
            .toStdString();

    ui->lineEdit_file->setText(QString::fromStdString(m_fileName));
}
