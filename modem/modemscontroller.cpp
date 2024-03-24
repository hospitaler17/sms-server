#include "modemscontroller.h"

ModemsController::ModemsController(QObject *parent)
    : QObject{parent}
{
    _statusTranslitor.insert(Modem::BUZY,       QString("Busy "));
    _statusTranslitor.insert(Modem::WAITING,    QString("Init "));
    _statusTranslitor.insert(Modem::READY,      QString("Ready"));
    _statusTranslitor.insert(Modem::ERROR,      QString("Error"));
}

ModemsController::~ModemsController()
{

}

void ModemsController::initModems(QString configDir)
{
    QDir dir;
    dir.setPath(configDir);
    if(!dir.exists())
        throw (QString("Config dir " + dir.path() + " does not exist!"));

    if(dir.isEmpty())
        throw (QString("Config dir " + dir.path() + " is empty!"));

    QStringList configList = dir.entryList(QDir::Files);

    for(const auto &config : configList)
    {
        if(config.contains(".conf"))
        {
            QSharedPointer<Modem> modem = QSharedPointer<Modem>::create(config);

            connect(modem.get(), SIGNAL(signalError(QString,QString)), this, SLOT(onErrorModem(QString,QString)));
            connect(modem.get(), SIGNAL(signalReady()), this, SLOT(onReadyModem()));
            connect(modem.get(), SIGNAL(signalBuzy()), SIGNAL(signalModemsStatusChange()));
            _modemsPtrList.append(modem);
        }
    }

    _modemsCount = _modemsPtrList.count();

    if(_modemsCount == 0)
        throw QString("Config dir " + dir.path() + " does not contains any *.configs files!");
}

bool ModemsController::send(QString number, QString text, bool writeInQueue)
{
    switch (_modemsCount)
    {
    case 0:
        throw QString("No modems inited!");
    case 1:
        if(tryToSend(1, number, text))
            return true;
        break;
    default:
        // NOTE: Для равномерной занятости всех модемов, использую случайное число
        // в промежутке от 1 до _modemsCount
        quint64 modemNumber = QRandomGenerator::global()->bounded(1, _modemsCount) - 1;
        // NOTE: Пробуем отправить на один из свободных модемов
        // NOTE: Начинаем от случайного и заканчиваем _modemsCount
        for(int i = modemNumber; i < _modemsCount; ++i)
        {
            if(tryToSend(i, number, text))
            {
                return true;
            }
        }
        // NOTE: Продолжаем от случайного-1 и заканчиваем 1
        for(int i = modemNumber-1; i > 0; --i)
        {
            if(tryToSend(i, number, text))
            {
                return true;
            }
        }
        break;
    }

    // Если сообщение не получилось отправить запишем в очередь и попробуем снова
    if(writeInQueue)
        _queueMessages.enqueue(MessagePair(number, text));

    return false;
}

QString ModemsController::getGlobalModemStatistcs()
{
    QString text;
    for(int i = 0; i < _modemsCount; ++i)
    {

        qDebug().noquote() << tr("|%1| %2 | %3 | s: %4| e: %5 |")

        // 1 Number
        .arg(QString::number(i+1))

        // 2 Name
        .arg(_modemsPtrList.at(i)->getFileName().left(16))

        // 3 Status
        .arg(_statusTranslitor.value(_modemsPtrList.at(i)->status()))

        // 4 Sended
        .arg(QString::number(_modemsPtrList.at(i)->getMessageCounter()))

        // 5 Errors
        .arg(QString::number(_modemsPtrList.at(i)->getErrorCounter()));
    }
    return text;
}

void ModemsController::onErrorModem(QString number, QString text)
{
    _queueMessages.enqueue(MessagePair(number, text));
    emit signalModemsStatusChange();
}

void ModemsController::onReadyModem()
{
    if(_queueMessages.count() > 0)
    {
//        auto modem = qobject_cast<Modem*>(sender());
        auto pair = _queueMessages.dequeue();       
        send(pair.first, pair.second);
    }
    emit signalModemsStatusChange();
}

bool ModemsController::tryToSend(int modem, const QString &number, const QString &text)
{
    if(modem > 0
            && modem < _modemsCount
            && _modemsPtrList.at(modem)->status() == Modem::READY)
    {
        _modemsPtrList.at(modem)->sendMessage(number, text);
        return true;
    }
    return false;
}
