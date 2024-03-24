#ifndef TRANSPORTLAYER_H
#define TRANSPORTLAYER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include <QDateTime>

class TransportLayer : public QObject
{
    Q_OBJECT

    using TCPSocketPtr = QTcpSocket*;
    using ListTCPSocketPtr = QHash<QHostAddress, TCPSocketPtr>;
    using QTcpServerPtr = QSharedPointer<QTcpServer>;

public:
    //! Конструктор класса транспортного уровеня
    explicit TransportLayer(QObject *parent = nullptr);

    ~TransportLayer();

    bool init();

protected slots:
    //! На новое подключение
    void onNewConnection();

    //! Слот на получение сообщения
    void onServerReadyRead();

    //! Слот на отключение сокета
    void onDisconnection();

private:
    //! Указатель на сервер
    QSharedPointer<QTcpServer> _server;

    //! Лист сокетов для обработки входящих сообщений
    ListTCPSocketPtr _socketList;
signals:
    //! Сигнал получения сообщения
    void signalNewMessageReceived(QString);
};

#endif // TRANSPORTLAYER_H
