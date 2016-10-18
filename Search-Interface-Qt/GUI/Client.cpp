#include "Client.h"

Client::Client(QObject *parent) : QThread(parent)
{
    networkSession = NULL;


    foreach (const QHostAddress &add, QNetworkInterface::allAddresses())
    {
        if (add.protocol() == QAbstractSocket::IPv4Protocol
            && add != QHostAddress(QHostAddress::LocalHost))
             address =  add;
    }

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readResult()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));


    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
        {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    }
}


Client::~Client()
{

}


void Client::sendQuery(const QString &query)
{
    qDebug() << __PRETTY_FUNCTION__ << "Start. " << endl;

    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(address, quint16(8888));
    // wait for 500ms then send the query
    tcpSocket->waitForConnected(500);

    if (tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << __PRETTY_FUNCTION__ << "Connected. Now send the query" << endl;
        this->writeToSocket<QString>(query);

        if(!this->isRunning())
        {
            qDebug() << __PRETTY_FUNCTION__ << "Starting the client thread." << endl;
            this->start();
        }
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << "Not Connected." << endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error: Client GUI");
        msgBox.setText("Not Connected to the server. Try searching again.");
        msgBox.exec();
    }

    qDebug() << __PRETTY_FUNCTION__ << "Complete. " << endl;
}


void Client::sendRelavanceFeedback(const FileInfo &fileInfo)
{
    writeToSocket<FileInfo>(fileInfo);
}

template <class T>
void Client::writeToSocket(const T &obj)
{

    // we encode the searchResult into a QByteArray using QDataStream.
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);              // we will serialize the data into the block
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << obj;                                                 // serialize a string
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
}


void Client::run()
{
	// Sloppy part, I thought it will last till tcpSocket->abort() is called, but no. 

    qDebug() << __PRETTY_FUNCTION__ << "WaitingForDisconnect." << endl;
    tcpSocket->waitForDisconnected(-1);
    qDebug() << __PRETTY_FUNCTION__ << "WaitingForDisconnect. Completed Waiting, end of run()." << endl;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SLOTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  */


void Client::readResult()
{
    qDebug() << __PRETTY_FUNCTION__ << endl;

    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
        return;
    in >> blockSize;
    if (tcpSocket->bytesAvailable() < blockSize)
        return;

    FileInfo fileInfo;
    int i; QString str;
    in >> i; in >> str;
    if (fileInfo.m_fileName.compare("lastMessageFromServer") == 0)
    {
        cout << __PRETTY_FUNCTION__ << "Last message received from Server: " << fileInfo << endl;
        emit signal_lastMessageFromServer(m_fileInfoVector);
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << "Received from Server: " << i << " " << str << endl;
        //m_fileInfoVector.push_back(fileInfo);

    }
}


void Client::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << __PRETTY_FUNCTION__ << endl;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Error: Client GUI");

    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        msgBox.setText("RemoteHostClosedError");
        break;
    case QAbstractSocket::HostNotFoundError:
        msgBox.setText("HostNotFoundError: The host was not found."
                       "Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        msgBox.setText("ConnectionRefusedError: The connection was refused by the peer.\n"
                       "Make sure the fortune server is running, and check"
                       "that the host name and port  settings are correct.");
        break;
    default:
        msgBox.setText(tr("Other: The following error occurred: %1.").arg(tcpSocket->errorString()));
    }
    msgBox.exec();
}


void Client::sessionOpened()
{
    qDebug() << __PRETTY_FUNCTION__ << endl;

    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}
