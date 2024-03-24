#ifndef CHECKER_H
#define CHECKER_H

#include <QObject>
#include <QRegularExpression>

class Checker : public QObject
{
    Q_OBJECT
public:
    explicit Checker(QObject *parent = nullptr);

    //! Функция проверки и чистки строки номера телефона
    static bool checkNumber(QString& number);

    //! Функция проверки и чистки строки текста
    static bool checkText(QString& text);

    //! Функция проверки и чистки строки числового кода
    static bool checkCode(QString& text);


signals:

};

#endif // CHECKER_H
