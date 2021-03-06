#include "config.h"
#include <QDir>
#include <QtCore/QtCore>

Config::Config(QString qstrfilename) {
    if (qstrfilename.isEmpty()) {
        fileName = this->getConfigPath() + "Config.ini";
    } else {
        fileName = this->getConfigPath() + qstrfilename;
    }

    cfg = new QSettings(fileName, QSettings::IniFormat);
    cfg->setIniCodec("UTF8");
}
Config::~Config() {
    delete cfg;
}
void Config::set(QString qstrnodename, QString qstrkeyname, QVariant qvarvalue) {
    cfg->setValue(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname), qvarvalue);
}

QVariant Config::get(QString qstrnodename, QString qstrkeyname) {
    QVariant qvar = cfg->value(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname));
    return qvar;
}

QString Config::getConfigPath() {
    return QDir::homePath() + "/.splitExcel/";
}
void Config::clear() {
    cfg->clear();
}
