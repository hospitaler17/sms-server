#ifndef CHECKER_H
#define CHECKER_H

#include <QObject>
#include <QRegularExpression>

class Checker : public QObject
{
    Q_OBJECT
public:
    explicit Checker(QObject *parent = nullptr);

    /*! \brief Функция проверки и чистки строки номера телефона
     *  \param number строка с номером телефона
     *  \return true если строка с номером телефона содержит только цифры, false в противном случае
     */
    static bool checkNumber(QString& number);

    /*! \brief Функция проверки и чистки строки текста
     *  \param text строка с текстом
     *  \return true если строка с текстом содержит только цифры, false в противном случае
     */
    static bool checkText(QString& text);

    /*! \brief Функция проверки и чистки строки числового кода
     *  \param text строка с числовым кодом
     *  \return true если строка с числовым кодом содержит только цифры, false в противном случае
     */
    static bool checkCode(QString& text);
};

#endif // CHECKER_H
