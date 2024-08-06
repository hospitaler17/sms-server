#ifndef ADMINKEYMODULEWRAPPER_H
#define ADMINKEYMODULEWRAPPER_H

#include <QObject>
#include <QLibrary>

class AdminkeyModuleWrapper : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AdminkeyModuleWrapper)

    typedef QByteArray (*tdQByteArray)();
    typedef bool (*tdBool)(QByteArray);

public:
    /*!
     * \brief Конструктор класса для работы с библиотекой AdminkeyModule.
     */
    explicit AdminkeyModuleWrapper(QObject *parent = nullptr);

    ~AdminkeyModuleWrapper();

    /*! 
     * \brief Инициализация модуля Административного ключа
     * \return В случае успеха возвращает true, иначе false
     */
    bool init(QString path = QString());

    /*! 
     * \brief Генерация ключа Административного ключа
     * \return В случае успеха возвращает true, иначе false
     */
    QByteArray generate();

    /*! 
     * \brief Проверка ключа Административного ключа
     * \return В случае успеха возвращает true, иначе false
     */
    bool check(const QByteArray& key);
    
protected:
    //! \brief Объект для работы с библиотекой
    QScopedPointer<QLibrary> lib { new QLibrary() };
};

#endif // ADMINKEYMODULEWRAPPER_H
