#ifndef MODEMSCONTROLLER_H
#define MODEMSCONTROLLER_H

#include <QObject>
#include <QDir>
#include <QQueue>
#include <QPair>
#include <QRandomGenerator>
#include <QDebug>
#include <QDateTime>

#include "common.h"
#include "modem.h"
#include "settings.h"

class ModemsController : public QObject
{
    Q_OBJECT

    using MessagePair = QPair<QString /*number*/, QString /*text*/>;
    using MessageQueue = QQueue<MessagePair>;
    using ModemsPtrList = QList<QSharedPointer<Modem>>;
public:
    explicit ModemsController(QObject *parent = nullptr);
    ~ModemsController();

    void initModems(QString configDir);

    bool send(QString number, QString text, bool writeInQueue = true);

    QString getGlobalModemStatistcs();

protected:
    MessageQueue _queueMessages;

    ModemsPtrList _modemsPtrList;

    int _modemsCount { 0 };

protected slots:
    void onErrorModem(QString number, QString text);

    void onReadyModem();
private:
    bool tryToSend(int modem, const QString& number, const QString& text);

    QHash<Modem::Status, QString> _statusTranslitor;

signals:

    void signalModemsStatusChange();
    //TODO: Сделать получение сообщений
    void messageRecieve(QDateTime/*date time*/,QString/*number sender*/,QString/*number reciever*/,QString/*text msg*/);
};

#endif // MODEMSCONTROLLER_H
