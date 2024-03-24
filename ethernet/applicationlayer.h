#ifndef APPLICATIONLAYER_H
#define APPLICATIONLAYER_H

#include <QObject>
#include <QRegularExpression>

#include "transportlayer.h"
#include "httppacket.h"


class ApplicationLayer : public QObject
{
    Q_OBJECT
public:
    //!

    //! Конструктор класса прикладного уровня получения
    explicit ApplicationLayer(QObject *parent = nullptr);

    bool init();

protected slots:
    //! Слот для получения нового сообщения от транспортного уровня
    void onNewMessage(QString msg);

private:
    //! Указатель на транспортный уровень
    QSharedPointer<TransportLayer> _transportLayer;

    //! Объект выделения GET пакетов
    QRegularExpression _re;

    //! Функция выделение запроса из всего сообщения
    QString getRequestFromMessage(QString message);

signals:
    //! Сигнал на получения запроса
    void signalNewRequest(HTTPPacket);

};

#endif // APPLICATIONLAYER_H
