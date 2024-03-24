#include <QCoreApplication>
#include <QDebug>
#include "checker.h"
#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    QCoreApplication::setApplicationName(QString::number(APP_NAME));
//    QCoreApplication::setApplicationVersion("1.0");

    QScopedPointer<MainController> controller(new MainController());
    if(!controller->init())
        return -1;

    return a.exec();
}
