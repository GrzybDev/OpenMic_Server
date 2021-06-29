#include "setupwizard.h"
#include "../MainWindow/mainwindow.h"

SetupWizard::SetupWizard(QWidget *parent) :
    QWizard(parent)
{
    parent_widget = parent;

    setWindowTitle(QObject::tr("OpenMic First Run Setup"));

    addPage(createIntroPage());
    addPage(createAudioDevicePage());
}

SetupWizard::~SetupWizard()
{

}

QWizardPage* SetupWizard::createIntroPage() {
    QWizardPage *page = new QWizardPage;
    page->setTitle(QObject::tr("Welcome to OpenMic!"));

    QLabel *label = new QLabel(QObject::tr("It seems that this is first time you're launching OpenMic Server on your PC, and that's why you're seeing this setup wizard.\n\n"
                                           "This app is responsible for communicating with your mobile device via USB or local network (LAN) and playing received audio data to virtual microphone, so you can use your phone as microphone in your PC apps.\n\n"
                                           "Setup wizard will make sure that OpenMic can work correctly, please follow instructions for the best out-of-box experience.\n\n"
                                           "When you're ready, press \"Next\" to continue."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}

QWizardPage* SetupWizard::createAudioDevicePage() {
    QWizardPage *page = new QWizardPage;
    page->setTitle(QObject::tr("Output Audio Device"));

    QLabel *label = new QLabel(QObject::tr("This is the most essential part of setup, please make sure that output audio device is set to loopback audio device AND NOT to your actual headphones/speakers (if you're using Windows, we recommend using VB-Audio device, but any loopback device will work)."));
    label->setWordWrap(true);

    QComboBox *comboBox = new QComboBox(this);
    connect(comboBox, SIGNAL(currentTextChanged(QString)), SLOT(saveAudioDevice(QString)));
    addAudioDevicesToCombobox(comboBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboBox);
    page->setLayout(layout);

    return page;
}

void SetupWizard::addAudioDevicesToCombobox(QComboBox *comboBox) {
    const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    QList<QString> knownDevices;

    for (const auto &device : deviceInfos) {
        if (knownDevices.contains(device.deviceName()))
            continue;

        QString deviceName = device.deviceName();
        comboBox->addItem(deviceName, deviceName);
        knownDevices.append(deviceName);
    }
}

void SetupWizard::saveAudioDevice(QString deviceName) {
    MainWindow* parent = qobject_cast<MainWindow*>(parent_widget);
    parent->appConfig->setValue("Audio", "Device", deviceName);
    parent->appConfig->applyChanges();
}
