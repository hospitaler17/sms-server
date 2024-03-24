#ifndef MODEM_H
#define MODEM_H

#include <QTimerEvent>
#include <QObject>
#include <QProcess>

#include "settings.h"


class Modem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status CONSTANT)

public:
    explicit Modem(const QString& configPath = "", QObject *parent = nullptr);
    ~Modem();

    enum Status
    {
        ERROR = -1,     ///< Ошибка
        WAITING = 0,    ///< Начальное|переходное сосотяние
        READY = 1,      ///< Готов
        BUZY = 2        ///< Занят
    };
    quint64 getErrorCounter() {return _errorCounter;}
    quint64 getMessageCounter() {return _messageCounter;}
    Status status() const;
    QString getFileName() const;


    void sendMessage(const QString& number, const QString &text);

protected:
    Status _status { WAITING };
    quint64 _errorCounter { 0 };
    quint64 _messageCounter { 0 };
    QString _configPath;

    uint _errorTimeout { 1000 };
    uint _answerTimeout { 5000 };
    uint _maxErrorCount { 0 };

    void setStatus(const Status newStatus, const QString& number = "", const QString &message = "");
    void timerEvent(QTimerEvent *e) override;

private:
    int _timerErrorID;
signals:
    void signalReady();
    void signalBuzy();
    void signalError(QString /*number*/, QString /*text*/);
};

#endif // MODEM_H
