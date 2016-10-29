#include "CacheManager.h"

CacheManager::CacheManager(QDialog* parent) : QDialog(parent), ui(new Ui::CacheManager)
{
    ui->setupUi(this);
    m_cache = Cache::instance();
}

CacheManager::~CacheManager()
{
    delete m_cache;
}

void CacheManager::on_applyButton_clicked()
{
    if (ui->simRadioButton->isChecked())
    {
        this->buildCache();
    }
    else if (ui->crawlRadioButton->isChecked())
    {
        // Crawl
        //Crawler crawler;
        //vector<FileInfo> fileInfovec = crawler.getFileList(m_crawlDiskPath);
        //for (FileInfo fileInfo : fileInfovec)
        //    addToCache(fileInfo);
    }

    this->close();
}


/*
 * Open the simulated data file.
 * Read the datafile, create fileinfo and add to cache.
 */
void CacheManager::buildCache()
{
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

    ifstream fs(FILE_SIM_DATA);
    // new lines will be skipped unless we stop it from happening:
    fs.unsetf(std::ios_base::skipws);
    // count the newlines with an algorithm specialized for counting:
    unsigned line_count = std::count(std::istream_iterator<char>(fs), std::istream_iterator<char>(), '\n');
    ui->progressBar->setMinimum(1);
    ui->progressBar->setMaximum(line_count);
    fs.close();

    m_cache->open();
    // TODO: This is inefficient, closing it and reopening it! Find a way to use fs agian.
    ifstream fs1(FILE_SIM_DATA);
    while (getline(fs1, line))
    {
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

        m_cache->add(fileInfo);

        ui->progressBar->setValue(++counter);
        ui->totalLabel->setText(QString::number(counter));

        #ifdef DBG_CACHE
        cout << __PRETTY_FUNCTION__ << fileInfo << endl;
        #endif
    }
    m_cache->close();
    fs1.close();
    this->close();
}
