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
    explicit AdminkeyModuleWrapper(QObject *parent = nullptr);

    bool init();

    QByteArray generate();
    bool check(const QByteArray& key);
private:

    QScopedPointer<QLibrary> lib { new QLibrary() };

signals:

};

#endif // ADMINKEYMODULEWRAPPER_H
