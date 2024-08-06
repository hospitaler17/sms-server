#include <QCoreApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QString>

#include "checker.h"
#include "maincontroller.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);

    const auto& settings = Settings::getInstance();

    //QCommandLineParser
    QCommandLineParser parser;
    parser.setApplicationDescription("Translate TCP request to sms due gnukki-cli");
    parser.addHelpOption();
    parser.addVersionOption();

    // A boolean option with multiple names (-h, --help)
    QCommandLineOption helpOption((QStringList() << "l" << "log"),
                                  QCoreApplication::translate("main",
                                                              (QString("Logginig all messages in dir \" %1 \"")
                                                               .arg(settings->getConfigDir().path()))
                                                              .toStdString()
                                                              .c_str()));

    parser.addOption(helpOption);

    parser.process(a);

    if(parser.isSet(helpOption))
    {
        qInfo() << parser.helpText();
        return 0;
    }

    QScopedPointer<MainController> controller(new MainController());
    if(!controller->init())
        return -1;

    return a.exec();
}
