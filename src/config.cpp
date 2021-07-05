#include "config.h"
#include "iostream"

Config::Config(QObject *parent)
	: QObject(parent)
{
	loadConfigMap();
	readConfig();
}

Config::~Config()
= default;

void Config::loadConfigMap()
{
    QMap<QString, QVariant> generalList;
    generalList["FirstRunCompleted"] = false;
    generalList["LoadModuleOnStart"] = false;

    QMap<QString, QVariant> audioList;
    audioList["Device"] = "";

	configMap["General"] = generalList;
    configMap["Audio"] = audioList;
}


void Config::readConfig()
{
    configData.clear();

    QList<QString> keys = configMap.keys();
    int keysCount = keys.count();

    for (int x = 0; x < keysCount; x++)
	{
        QString category = keys.at(x);
        QMap<QString, QVariant> data;

        QMap<QString, QVariant> entryMap = configMap[category];
        QList<QString> entryKeys = entryMap.keys();

        int entryCount = entryKeys.count();

        for (int y = 0; y < entryCount; y++) {
            QString entryName = entryKeys.at(y);
            QVariant entryDefaultValue = entryMap[entryName];

            data[entryName] = settings.value(category + "/" + entryName, entryDefaultValue);
        }

        configData[category] = data;
    }
}

QVariant Config::getValue(QString category, QString settingname) {
    return configData[category][settingname];
}

void Config::setValue(QString category, QString settingname, QVariant value) {
    configData[category][settingname] = value;
    modifiedValues.append(category + "/" + settingname);
}

void Config::revertChanges() {
    modifiedValues.clear();
    readConfig();
}

void Config::applyChanges() {
    foreach (auto valueChanged, modifiedValues) {
        QStringList valuePath = valueChanged.split("/");
        settings.setValue(valueChanged, configData[valuePath[0]][valuePath[1]]);
    }

    modifiedValues.clear();
    readConfig();
}

bool Config::isModified() {
    return modifiedValues.count() != 0;
}
