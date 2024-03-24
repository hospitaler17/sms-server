#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>

class XMLParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLParser(QObject *parent = nullptr);

    bool init();

    //! Считывание параметров из XML файла
    bool readXmlFile(const QString& pathToFile);

signals:

};

#endif // XMLPARSER_H
