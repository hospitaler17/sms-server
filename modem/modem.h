#ifndef MODEM_H
#define MODEM_H

#include <QTimerEvent>
#include <QObject>
#include <QProcess>

#include "settings.h"


class Modem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status CONSTANT)

public:
    /*!
    \brief Конструктор класса Modem
    \param[in] configPath Путь до файла конфигураций
    */
    explicit Modem(const QString& configPath = "", QObject *parent = nullptr);

    //! \brief Деструктор класса модем
    ~Modem();

    //! Cтатус модема
    enum Status
    {
        ERROR = -1,     ///< Ошибка
        WAITING = 0,    ///< Начальное|переходное сосотяние
        READY = 1,      ///< Готов
        BUZY = 2        ///< Занят
    };

    //! \brief Функция получения счетчика ошибок
    quint64 getErrorCounter() {return _errorCounter;}

    //! \brief Функция получения счетчика отправленных сообщений
    quint64 getMessageCounter() {return _messageCounter;}

    //! \brief Функция получения статуса модема
    Status status() const;

    //! \brief Функция получения именя файла кофигурации (имени модема)
    QString getFileName() const;

    /*!
     * \brief Функция для отправки SMS сообщения
     * \param number Номер телефона
     * \param text Текст SMS сообщения
     */
    void sendMessage(const QString& number, const QString &text);

protected:
    //! \brief Статус модема
    Status _status { WAITING };

    //! \brief Счетчик ошибок
    quint64 _errorCounter { 0 };

    //! \brief Счетчик отправленных сообщений
    quint64 _messageCounter { 0 };

    //! \brief Путь до файла конфигурации
    QString _configPath;

    /*! \brief Таймаут при ошибке отправке */
    uint _errorTimeout { 1000 };

    //! \brief Таймаут получения ответа от программы отправителя
    uint _answerTimeout { 5000 };

    //! \brief Максимальное значение ошибок для отправки сообщений
    uint _maxErrorCount { 0 };

    //! \brief Уставнока статуса модема
    void setStatus(const Status newStatus, const QString& number = "", const QString &message = "");

    //! \brief Функция обработки срабатывания таймеров
    void timerEvent(QTimerEvent *e) override;

private:
    //! \brief ID таймера при ошибки
    int _timerErrorID;

signals:
    //! \brief Сигнал при изменении статуса на "ГОТОВ"
    void signalReady();

    //! \brief Сигнал при изменении статуса на "ЗАНЯТ"
    void signalBuzy();

    /*!
     * \brief Сигнал отправляемый при переходе к состоянию "ОШИБКА".
     * Сигналом возвращается номер телефона и сообщение, чтобы они снова вернулись в очередь на отправку.
     * \param number номер телефона, при отправке на который произошла ошибка
     * \param text текст сообщения
     */
    void signalError(QString /*number*/, QString /*text*/);
};

#endif // MODEM_H
