#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QAudioDeviceInfo>

class SetupWizard : public QWizard
{
    Q_OBJECT

public:
    explicit SetupWizard(QWidget *parent = nullptr);
    ~SetupWizard();

private slots:
    void saveAudioDevice(QString deviceName);

private:
    QWidget* parent_widget;

    QWizardPage* createIntroPage();
    QWizardPage* createAudioDevicePage();

    void addAudioDevicesToCombobox(QComboBox* comboBox);
};

#endif // SETUPWIZARD_H
