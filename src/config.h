#pragma once

#include <QObject>
#include <QSettings>


class Config final : public QObject
{
	Q_OBJECT

public:
	explicit Config(QObject *parent);
	~Config() override;

    QVariant getValue(QString category, QString settingname);
    void setValue(QString category, QString settingname, QVariant value);

    void revertChanges();
    void applyChanges();
    bool isModified();

private:
	void loadConfigMap();
	void readConfig();

	QSettings settings;
	QMap<QString, QMap<QString, QVariant>> configData;
    QMap<QString, QMap<QString, QVariant>> configMap;

    QList<QString> modifiedValues;
};
