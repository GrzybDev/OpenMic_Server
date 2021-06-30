#include "setupwizard.h"
#include "../MainWindow/mainwindow.h"

SetupWizard::SetupWizard(QWidget *parent) :
    QWizard(parent)
{
    parent_widget = parent;

    setWindowTitle(QObject::tr("OpenMic First Run Setup"));

    addPage(createIntroPage());
    addPage(createAudioDevicePage());
    addPage(createNetworkDevicePage());
    addPage(createEndingPage());
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

    QLabel *label_2 = new QLabel(QObject::tr("When you're ready, click \"Next\" to continue."));
    label_2->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addWidget(label_2);
    page->setLayout(layout);

    return page;
}

QWizardPage* SetupWizard::createNetworkDevicePage() {
    QWizardPage *page = new QWizardPage;
    page->setTitle(QObject::tr("Network Device"));

    QLabel *label = new QLabel(QObject::tr("Now, select your network card, it should be connected to the same network as your phone. (Note: If you'll be using USB communication you can skip this step by clicking Next)"));
    label->setWordWrap(true);

    QComboBox *comboBox = new QComboBox(this);
    connect(comboBox, SIGNAL(currentTextChanged(QString)), SLOT(saveNetworkDevice(QString)));
    addNetworkDevicesToCombobox(comboBox);

    QLabel *label_2 = new QLabel(QObject::tr("When you're ready, click \"Next\" to continue."));
    label_2->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addWidget(label_2);
    page->setLayout(layout);

    return page;
}

QWizardPage* SetupWizard::createEndingPage() {
    QWizardPage *page = new QWizardPage;
    page->setTitle(QObject::tr("You're all set!"));

    QLabel *label = new QLabel(QObject::tr("That's it! OpenMic Server is now ready for the action!<br/><br/>"
                                           "If you haven't already, download \"OpenMic Client\" from Google Play! (<a href=\"https://grzybmic.web.app/googleplay\">https://grzybmic.web.app/googleplay</a>)<br/><br/>"
                                           "To start using this app select \"Connect\" from Device menu and follow on-screen instructions.<br/><br/>"
                                           "I hope you'll find this app useful!"));
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    label->setOpenExternalLinks(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
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

void SetupWizard::saveNetworkDevice(QString deviceName) {
    MainWindow* parent = qobject_cast<MainWindow*>(parent_widget);
    parent->appConfig->setValue("Network", "Device", deviceName);
    parent->appConfig->applyChanges();
}

void SetupWizard::addNetworkDevicesToCombobox(QComboBox *comboBox) {
    const auto interfaces = QNetworkInterface::allInterfaces();
    QList<QString> knownInterfaces;

    foreach (QNetworkInterface interface, interfaces) {
        if (knownInterfaces.contains(interface.humanReadableName()))
            continue;

        QString interfaceName = interface.humanReadableName();
        comboBox->addItem(interfaceName, interfaceName);
        knownInterfaces.append(interfaceName);
    }
}
