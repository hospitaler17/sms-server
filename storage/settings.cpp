#include "settings.h"

Settings* Settings::_instance = nullptr;

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    _settings = QSharedPointer<QSettings>::create("settings.ini", QSettings::IniFormat);
}

Settings* Settings::getInstance()
{
    if(!_instance)
            _instance = new Settings();
    return _instance;
}

void Settings::sync()
{
    if(_settings)
        _settings->sync();
}



QDir Settings::getConfigDir() const
{
    return QDir(_settings->value("modems/config_dir", "configs").toString());
}

uint Settings::getErrorTimeOut() const
{
    bool ok = false;
    uint value = _settings->value("modems/error_timeout", _errorTimeout).toUInt(&ok);
    if(ok && value >= 1000)
        return value;
    return _errorTimeout;
}

uint Settings::getAnswerTimeOut() const
{
    bool ok = false;
    uint value = _settings->value("modems/answer_timeout", _answerTimeout).toUInt(&ok);
    if(ok && value >= 1000)
        return value;
    return _answerTimeout;
}

uint Settings::getResendTimeOut() const
{
    bool ok = false;
    uint value = _settings->value("modems/resend_timeout", _resendTimeout).toUInt(&ok);
    if(ok && value >= 500)
        return value;
    return _resendTimeout;
}

uint Settings::getMaxErrorCount() const
{
    return _settings->value("modems/max_error_count", 0).toUInt();
}

quint16 Settings::getListenPort() const
{
    return _settings->value("ethernet/listen_port", 8080).toUInt();
}

QDir Settings::getLogDir() const
{
    return QDir(_settings->value("logger/dir", "logs").toString());
}

uint Settings::getLogSize() const
{
    return _settings->value("logger/log_size", MB(5)).toUInt();
}


///just example
//Settings::THEME Settings::getThemeType() const
//{
//    return THEME(_settings->value("theme/type", 0).toInt());
//}

//void Settings::setThemeType(THEME type)
//{
//    _settings->setValue("theme/type", type);
//}
