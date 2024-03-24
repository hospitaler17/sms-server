#include "checker.h"

Checker::Checker(QObject *parent)
    : QObject{parent}
{

}

bool Checker::checkNumber(QString &number)
{
    //NAND format XXXX-XXX-XXX
    QRegularExpression  re;

    //Clear all bed signs
    re.setPattern("[^0-9]");
    number.remove(re);

    //RU
    re.setPattern("[7]|[8][0-9]{10}");
    if(QRegularExpression::NormalMatch != re.match(number).matchType())
        return false;
    if(number.at(0) == QChar('7'))
        number.push_front(QChar('+'));

    //ALL RIGHT
    return true;
}

bool Checker::checkText(QString &text)
{
    if(text.length() == 0)
        return false;

    QRegularExpression  re;
    re.setPattern(";|/|\"|\'|&|sudo|rm");
    text.remove(re);

    if(text.length() == 0)
        return false;

    text.replace("_", " ");

    //ALL RIGHT
    return true;
}

bool Checker::checkCode(QString &text)
{
    if(text.length() == 0)
        return false;

    QRegularExpression  re;
    re.setPattern("[^0-9]");
    text.remove(re);

    if(text.length() == 0)
        return false;

    //ALL RIGHT
    return true;

}

