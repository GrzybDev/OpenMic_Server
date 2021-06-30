#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QAudioDeviceInfo>
#include <QNetworkInterface>

class SetupWizard : public QWizard
{
    Q_OBJECT

public:
    explicit SetupWizard(QWidget *parent = nullptr);
    ~SetupWizard();

private slots:
    void saveAudioDevice(QString deviceName);
    void saveNetworkDevice(QString deviceName);

private:
    QWidget* parent_widget;

    QWizardPage* createIntroPage();
    QWizardPage* createAudioDevicePage();
    QWizardPage* createNetworkDevicePage();
    QWizardPage* createEndingPage();

    void addAudioDevicesToCombobox(QComboBox* comboBox);
    void addNetworkDevicesToCombobox(QComboBox* comboBox);
};

#endif // SETUPWIZARD_H
