#include "adminkeymodulewrapper.h"
#include <QDir>

AdminkeyModuleWrapper::AdminkeyModuleWrapper(QObject *parent)
    : QObject{parent}
{

}

bool AdminkeyModuleWrapper::init()
{
    lib->setFileName(QDir("libs").filePath("libAdminkeyModule"));

    if (!lib->load())
    {
        qDebug() << lib->errorString();
        return false;
    }
    return true;
}

QByteArray AdminkeyModuleWrapper::generate()
{
    if(lib->isLoaded())
    {
        tdQByteArray generateKey = (tdQByteArray)lib->resolve("generate");
        if (generateKey)
            return generateKey();
    }
    return QByteArray();
}

bool AdminkeyModuleWrapper::check(const QByteArray &key)
{
    if(lib->isLoaded())
    {
        tdBool checkKey = (tdBool)lib->resolve("check");
        if(checkKey)
            return checkKey(key);
    }
    return true;
}
