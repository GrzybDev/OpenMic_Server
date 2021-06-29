#pragma once

#include <QObject>
#include <QSettings>


class Config final : public QObject
{
	Q_OBJECT

public:
	explicit Config(QObject *parent);
	~Config() override;
private:
	void loadConfigMap();
	void readConfig();

	QSettings settings;
	QMap<QString, QMap<QString, QVariant>> configData;

	QMap<QString, QList<QString>> configMap;
};
