#ifndef HTTPPACKET_H
#define HTTPPACKET_H

#include <QObject>
#include <QHostAddress>

class HTTPPacket : public QObject
{
    Q_OBJECT
public:
    //! Enum типа запросов
    enum class  METHOD
    {
        GET,
        POST
    };

    HTTPPacket(QString message = "", QObject *parent = nullptr);
    HTTPPacket(const HTTPPacket& old);

    const QString &message() const;
    void setMessage(const QString &newMessage);

    METHOD method() const;

    const QString &versionHttp() const;

    const QString &userAgentString() const;

    const QHostAddress &hostAddress() const;

    const QStringList &acceptLanguageList() const;

    const QStringList &acceptEncodingList() const;

    const QStringList &acceptList() const;

    quint16 hostPort() const;



    const QString &requestString() const;

    const QString &requestStringPath() const;

    const QHash<QString, QString> &requestParameters() const;

public slots:
    //! Функция разбора сообщения
    bool parse();
    bool parse(const QString& message);

private:
    //! Неразобранный запрос (как есть)
    QString _message;

    //! Тип запроса
    METHOD _method{METHOD::GET};

    //! Номер версии HTTP
    QString _versionHttp;

    //! Строка запроса
    QString _requestString;
    QString _requestStringPath;
    QHash<QString/*parameter*/,QString/*value*/> _requestParameters;

    //! Параметр HOST:
    //! хост, к которому идёт обращение
    QHostAddress _hostAddress;

    //! порт, по которому идёт обращение
    quint16 _hostPort {0};

    //! Параметр User-Agent:
    //! характеристики клиента, с которого осуществляется выход, например название и версия браузера
    QString _userAgentString;

    //! Параметр Accept:
    //! определяет, какие типы данных может обработать клиент
    QStringList _acceptList;

    //! Параметр Accept-Encoding:
    //! обозначает форматы и кодировку файлов
    QStringList _acceptEncodingList;

    //! Параметр Accept-Language:
    //! указывает на принимаемые языки
    QStringList _acceptLanguageList;

    //! Функция разбора строки запроса в теле http заголовка
    bool parseRequestLine(QString requestLine);

    //! Функция разделитель по строке с проверкой
    bool split(QString string, QStringList& splittedStringList, const QString& splitter, const uint countCheck = 0);

signals:

};

#endif // HTTPPACKET_H
