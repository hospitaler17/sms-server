#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "settings.h"
#include "modemscontroller.h"
#include "applicationlayer.h"
#include "logger.h"
#include "checker.h"
#include "adminkeymodulewrapper.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    //! Конструктор главного связующего класса
    explicit MainController(QObject *parent = nullptr);

    //! Инициализация зависимых классов
    bool init();

public slots:
    //! Слот для печати состояния модема в строку
    void printModemStatus();

    //! Слот для получения и разбора TCP пакета
    void slotNewRequest(HTTPPacket packet);

protected:
    //! Функция инициализации контроллера модемов
    bool initModemsController();

    //! Функция инициализации TCP врат
    bool initEthernetGate();

    //! Функция инициализации файлового логера программы
    bool initLogger();

    //! Функция инициализации модуля административного ключа
    bool initAdminKeyModule();

    //! Функция отправки числового кода
    void sendCode(const HTTPPacket& packet);

    //! Функция отправки текста
    void sendText(const HTTPPacket& packet);

    //! Функция проверки ключа
    bool checkAPIKey(const QString& key);

private:
    //! Умный указатель на контроллер модемов
    QSharedPointer<ModemsController> _modemsController;

    //! Умный указатель на TCP врата
    QSharedPointer<ApplicationLayer> _ethernetGate;

    //! Умный указатель на логгер
    QSharedPointer<Logger> _logger;

    //! Умный указатель на врапер для библиотеки проверки административного ключа
    QSharedPointer<AdminkeyModuleWrapper> _adminkeyModule;

signals:

};

#endif // MAINCONTROLLER_H
