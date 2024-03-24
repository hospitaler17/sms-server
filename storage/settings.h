#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QSharedPointer>

#include <QDir>

#define MB(x) (x*1048576)
#define KB(x) (x*1024)

class Settings : public QObject
{
    Q_OBJECT

public:

    virtual ~Settings(){};
    static Settings* getInstance();
    void sync();

    //config dir path
    QDir getConfigDir() const;

    //modems timeouts
    uint getErrorTimeOut() const;
    uint getAnswerTimeOut() const;
    uint getResendTimeOut() const;
    uint getMaxErrorCount() const;

    //ethernet
    quint16 getListenPort() const;

    //logger
    QDir getLogDir() const;
    uint getLogSize() const;

private:
    Settings(QObject * parent = nullptr);
    static Settings* _instance;

    QSharedPointer<QSettings> _settings;

    const uint _errorTimeout { 5000 };
    const uint _answerTimeout { 10000 };
    const uint _resendTimeout { 1000 };

signals:

};

#endif // SETTINGS_H
