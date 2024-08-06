#ifndef MODEMSCONTROLLER_H
#define MODEMSCONTROLLER_H

#include <QObject>
#include <QDir>
#include <QQueue>
#include <QPair>
#include <QRandomGenerator>
#include <QDebug>
#include <QDateTime>

#include "common.h"
#include "modem.h"
#include "settings.h"

class ModemsController : public QObject
{
    Q_OBJECT

    using MessagePair = QPair<QString /*number*/, QString /*text*/>;
    using MessageQueue = QQueue<MessagePair>;
    using ModemsPtrList = QList<QSharedPointer<Modem>>;

public:
    //! Конструктор класса ModemsController
    /*!
     * \brief Конструктор класса ModemsController.
     * Используется для создания и управлением классов Modem
     */
    explicit ModemsController(QObject *parent = nullptr);
    ~ModemsController();

    /*!
     * \brief Функция инициализации модемов
     * \param configDir Путь до каталога с конфигурационными файлами модемов
     */
    void initModems(QString configDir);

    /*!
     * \brief Отправка сообщенния
     * \param number Номер телефона
     * \param text Текст сообщения
     * \param writeInQueue Признак записи сообщения в очередь при занятости всех модемов
     * \return Признако удочной передачи сообщения до отправки модемом
     */
    bool send(QString number, QString text, bool writeInQueue = true);

    /*!
     * \brief Получение строки со статистикой модемов
     * \return Строка со статистикой модемов в табличном виде
     */
    QString getGlobalModemStatistcs();

protected:
    //! \brief Переменная для хранения очереди сообщений
    MessageQueue _queueMessages;

    //! \brief Переменная для хранения списка модемов
    ModemsPtrList _modemsPtrList;

    //! \brief Переменная для хранения счетчика модемов
    int _modemsCount { 0 };

protected slots:
    /*!
     * \brief Слот обработки события смены сосотяния на "Ошибка" у модема
     * \param number Номер телефона
     * \param text Текст сообщения
     */
    void onErrorModem(QString number, QString text);

    //! \brief Слот обработки события смены состояния на "Готов" у модема
    void onReadyModem();

private:
    /*!
     * \brief Попытка отправки сообщения через указанный порядковый номер модема
     * \param number Номер телефона
     * \param text Текст сообщения
     * \return Признако удачной передачи сообщения до отправки в модем
     */
    bool tryToSend(int modem, const QString& number, const QString& text);

    //! \brief Хеш-таблица для перевода статусов модемов в текст
    QHash<Modem::Status, QString> _statusTranslitor;

signals:
    //! \brief Сигнал смены состояния модемов
    void signalModemsStatusChange();
    
    //TODO: Сделать получение сообщений
    void messageRecieve(QDateTime/*date time*/,QString/*number sender*/,QString/*number reciever*/,QString/*text msg*/);
};

#endif // MODEMSCONTROLLER_H
