#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <QDialog>
#include <QTcpSocket>
#include <QtWidgets>
#include <QtNetwork>
#include <QThread>

#include "FileInfo.h"

using namespace std;

class Client : public QThread
{
    Q_OBJECT

private:
    QHostAddress address;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;
    vector<FileInfo> m_fileInfoVector;

    template <class T>
    void writeToSocket(const T &obj);

public:
    Client(QObject *parent = 0);
    ~Client();
    void run();
    void sendQuery(const QString &query);
    void sendRelavanceFeedback(const FileInfo &fileInfo);

signals:
    void signal_lastMessageFromServer(vector<FileInfo> &fileInfoVector);

private slots:
    void readResult();
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();

};

#endif // CLIENT_H
