#include "logger.h"

static bool isInited{false};
static QFile* logFile;
static QHash<QtMsgType, QString> _msgTypeDescriptor;
static uint _maxSize;
static bool _debugPrint {false};

Logger::Logger(QObject *parent)
    : QObject{parent}
{
    logFile = Q_NULLPTR;

    _msgTypeDescriptor.insert(QtDebugMsg,       QString("Debug      "));
    _msgTypeDescriptor.insert(QtInfoMsg,        QString("Information"));
    _msgTypeDescriptor.insert(QtCriticalMsg,    QString("Critical   "));
    _msgTypeDescriptor.insert(QtWarningMsg,     QString("Warning    "));
    _msgTypeDescriptor.insert(QtSystemMsg,      QString("System     "));
    _msgTypeDescriptor.insert(QtFatalMsg,       QString("Fatal      "));

    _maxSize = Settings::getInstance()->getLogSize();

}

Logger::~Logger()
{
    if(logFile != nullptr)
        logFile->close();
}

bool Logger::init()
{
    if(isInited)
        return false;

    if( !startNewFile())
        return false;

    qInfo() << "Start programm";

    qInstallMessageHandler(Logger::messageOutput);

    isInited = true;
    return true;
}

bool Logger::startNewFile()
{
    QString fileName = tr("%1.log")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"));
    QDir dir = Settings::getInstance()->getLogDir();
    if(!dir.exists())
        dir.mkpath(dir.absolutePath());

    if(isInited || logFile)
    {
        logFile->write(tr("Start new log file: %1").arg(fileName).toStdString().c_str());
        logFile->flush();
        logFile->close();
    }
    else
        logFile = new QFile;

    logFile->setFileName(dir.filePath(fileName));
    logFile->open(QIODevice::Append | QIODevice::Text);
    if(!logFile->isOpen())
    {
        qCritical() << "Cannot create file" << fileName;
        return false;
    }
    return true;
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(logFile == nullptr && !logFile->isOpen())
        return;

    QString log= tr("[%1] %2: %3 %4\n")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"))
            .arg(_msgTypeDescriptor.value(type))
            .arg(context.function)
            .arg(msg);

    qDebug() << QString(msg).replace("\\\\", "\\");

    logFile->write(log.toLocal8Bit());
    logFile->flush();

    if(logFile->size() >= _maxSize)
        startNewFile();
}

