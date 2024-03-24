#include "modem.h"

Modem::Modem(const QString &configPath, QObject *parent)
    : QObject{parent},
      _configPath{configPath}
{
    if(!configPath.isEmpty() && configPath.contains(".config"))
        setStatus(READY);

    Settings * settings = Settings::getInstance();
    _errorTimeout = settings->getErrorTimeOut();
    _answerTimeout = settings->getAnswerTimeOut();
    _maxErrorCount = settings->getMaxErrorCount();
}

Modem::~Modem()
{

}

Modem::Status Modem::status() const
{
    return _status;
}

QString Modem::getFileName() const
{
    return QFileInfo(_configPath).baseName();
}

void Modem::sendMessage(const QString &number, const QString& text)
{
    setStatus(BUZY);
    QString command = tr("echo \"") + text + tr("\" | sudo gnokii --config ") + _configPath +  tr(" --sendsms ") + number;

    QProcess process;

    process.start(command);
    if(!process.waitForStarted())
    {
        setStatus(ERROR, number, text);
        return;
    }

    if(!process.waitForFinished(_answerTimeout))
    {
        process.terminate();
        setStatus(ERROR, number, text);
        return;
    }

    QByteArray answer = process.readAll();
    if(answer.contains("succeeded"))
        setStatus(READY);
    else
        setStatus(ERROR, number, text);
}

void Modem::setStatus(const Status newStatus, const QString &number, const QString& message)
{
    _status = newStatus;
    switch (_status)
    {
    case READY:
        emit signalReady();
        break;
    case BUZY:
        _messageCounter++;
        emit signalBuzy();
        break;
    case ERROR:
        _messageCounter--;
        _errorCounter++;
        emit signalError(number, message);
        if(_errorCounter < _maxErrorCount)
            _timerErrorID = startTimer(_errorTimeout);
        break;
    default:
        break;
    }
}

void Modem::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == _timerErrorID)
    {
        killTimer(_timerErrorID);
        setStatus(READY);
    }
}
