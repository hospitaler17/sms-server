#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QHash>
#include <QDateTime>
#include <QDebug>

#include "settings.h"


class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();
    static bool init();

protected:
    static bool startNewFile();

    static void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);

signals:

};

#endif // LOGGER_H
