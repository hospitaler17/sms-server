#include "maincontroller.h"
#include <QLibrary>

MainController::MainController(QObject *parent)
    : QObject{parent}
{

}

bool MainController::init()
{
    initLogger();

    initAdminKeyModule();

    if( !initModemsController() )
        return false;

    if( !initEthernetGate())
        return false;

    return true;
}

void MainController::printModemStatus()
{
    QString line = "===============================================================\n";
    qDebug().noquote() << line.toLocal8Bit().data() ;
    _modemsController->getGlobalModemStatistcs();
    qDebug().noquote() << "===============================================================\n";
}

void MainController::slotNewRequest(HTTPPacket packet)
{
    if(checkAPIKey(packet.requestParameters().value("key")))
    {
        return;
    }

    if(packet.requestStringPath().contains("send_code", Qt::CaseInsensitive))
    {
        sendCode(packet);
    }
    else if(packet.requestStringPath().contains("send_text", Qt::CaseInsensitive))
    {
        sendText(packet);
    }
}

bool MainController::initModemsController()
{
    try
    {
        _modemsController = QSharedPointer<ModemsController>::create();
        _modemsController->initModems(Settings::getInstance()->getConfigDir().absolutePath());
        printModemStatus();
        connect(_modemsController.get(), SIGNAL(signalModemsStatusChange()), this, SLOT(printModemStatus()));
    }
    catch (QString & error)
    {
        qCritical() << tr("Cannot init modems: %1").arg(error);
        return false;
    }
    qInfo() << "Modems init susseed";
    return true;
}

bool MainController::initEthernetGate()
{
    _ethernetGate = QSharedPointer<ApplicationLayer>::create();
    if( !_ethernetGate->init()){
        qCritical() << tr("Cannot init ethernet");
        return false;
    }

    connect(_ethernetGate.get(), SIGNAL(signalNewRequest(HTTPPacket)), this, SLOT(slotNewRequest(HTTPPacket)));

    qInfo() << "Ethernet init susseed";
    return true;
}

bool MainController::initLogger()
{
    _logger = QSharedPointer<Logger>::create();
    if(!_logger->init())
    {
        qCritical() << tr("Cannot init logger");
        return false;
    }
    qInfo() << "Logger init susseed";
    return true;
}

bool MainController::initAdminKeyModule()
{
    _adminkeyModule = QSharedPointer<AdminkeyModuleWrapper>::create();
    if(!_adminkeyModule->init())
    {
        qInfo() << "Cannot init AdminKeyModule";
        return false;
    }
    qInfo() << "AdminKeyModule init susseed";
    return true;
}

void MainController::sendCode(const HTTPPacket &packet)
{
    QString number = packet.requestParameters().value("number");
    QString text = packet.requestParameters().value("text");

    if(!Checker::checkNumber(number) || !Checker::checkCode(text))
        return;

    _modemsController->send(number, text);
}

void MainController::sendText(const HTTPPacket &packet)
{
    QString number = packet.requestParameters().value("number");
    QString text = packet.requestParameters().value("text");

    if(!Checker::checkNumber(number) || !Checker::checkText(text))
        return;

    //TODO: add option for IP adding forward in text

    _modemsController->send(number, text);
}

bool MainController::checkAPIKey(const QString &key)
{
    bool result = _adminkeyModule->check(QByteArray::fromHex(key.toLocal8Bit()));
    return result;
}
