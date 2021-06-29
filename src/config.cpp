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
	QList<QString> generalList;
	generalList.append("FirstRunCompleted");

	configMap["General"] = generalList;
}


void Config::readConfig()
{
	std::cout << "READING CONFIG" << std::endl;

	for (int x = 0; x < configMap.keys().count(); x++)
	{
		QString category = configMap.keys().at(x);
		std::cout << category.toStdString() << std::endl;
	}
}
