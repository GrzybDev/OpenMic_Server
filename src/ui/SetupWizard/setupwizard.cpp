#include "setupwizard.h"
#include "../MainWindow/mainwindow.h"

SetupWizard::SetupWizard(QWidget *parent) : QWizard(parent)
{
    parent_widget = parent;

    setWindowTitle(tr("OpenMic First Run Setup"));
    setOption(QWizard::NoCancelButton);
    WindowTools::disableTitleBarButtons(this);

    addPage(createIntroPage());
#ifdef Q_OS_LINUX
    addPage(createLinuxKernelModulePage());
#endif
    addPage(createAudioDevicePage());
    addPage(createNetworkDevicePage());
    addPage(createEndingPage());

    connect(this, SIGNAL(currentIdChanged(int)), SLOT(onPageChanged(int)));
}

SetupWizard::~SetupWizard()
{
}

QWizardPage *SetupWizard::createIntroPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("Welcome to OpenMic!"));

    QLabel *label = new QLabel(tr("It seems that this is first time you're launching OpenMic Server on your PC, and that's why you're seeing this setup wizard.\n\n"
                                  "This app is responsible for communicating with your mobile device via USB or local network (LAN) and playing received audio data to virtual microphone, so you can use your phone as microphone in your PC apps.\n\n"
                                  "Setup wizard will make sure that OpenMic can work correctly, please follow instructions for the best out-of-box experience.\n\n"
                                  "When you're ready, press \"Next\" to continue."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}

QWizardPage *SetupWizard::createLinuxKernelModulePage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("Linux Kernel Module"));

    QLabel *label = new QLabel(tr("You're running this app under Linux based operating system. OpenMic app can try to load kernel module `snd-aloop` on launch. This module adds special virtual loopback audio devices that OpenMic will use to send audio data.\n\n"
                                  "Note: OpenMic on Linux is designed to work with `snd-aloop` module, but it's not required, any loopback device will work (or even your actual headphones/speakers, depends on your need)."));
    label->setWordWrap(true);

    QCheckBox *checkBox = new QCheckBox(this);
    connect(checkBox, SIGNAL(stateChanged(int)), SLOT(setLoadKernelModuleState(int)));
    checkBox->setText(tr("Load `snd-aloop` on application start"));

    QLabel *label_2 = new QLabel(tr("When you're ready, click \"Next\" to continue."));
    label_2->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(checkBox);
    layout->addWidget(label_2);
    page->setLayout(layout);

    return page;
}

QWizardPage *SetupWizard::createAudioDevicePage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("Output Audio Device"));

    QLabel *label = new QLabel(tr("This is the most essential part of setup, please make sure that output audio device is set to loopback audio device AND NOT to your actual headphones/speakers (if you're using Windows, we recommend using VB-Audio device, but any loopback device will work)."));
    label->setWordWrap(true);

    audioComboBox = new QComboBox(this);
    connect(audioComboBox, SIGNAL(currentTextChanged(QString)), SLOT(saveAudioDevice(QString)));
    addAudioDevicesToCombobox();

    QLabel *label_2 = new QLabel(tr("When you're ready, click \"Next\" to continue."));
    label_2->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(audioComboBox);
    layout->addWidget(label_2);
    page->setLayout(layout);

    return page;
}

QWizardPage *SetupWizard::createNetworkDevicePage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("Network Device"));

    QLabel *label = new QLabel(tr("Now, select your network card, it should be connected to the same network as your phone. (Note: If you'll be using USB communication you can skip this step by clicking Next)"));
    label->setWordWrap(true);

    QComboBox *comboBox = new QComboBox(this);
    connect(comboBox, SIGNAL(currentTextChanged(QString)), SLOT(saveNetworkDevice(QString)));
    addNetworkDevicesToCombobox(comboBox);

    QLabel *label_2 = new QLabel(tr("When you're ready, click \"Next\" to continue."));
    label_2->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(comboBox);
    layout->addWidget(label_2);
    page->setLayout(layout);

    return page;
}

QWizardPage *SetupWizard::createEndingPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle(tr("You're all set!"));

    QLabel *label = new QLabel(tr("That's it! OpenMic Server is now ready for the action!<br/><br/>"
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

void SetupWizard::addAudioDevicesToCombobox()
{
    audioComboBox->clear();

    const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    QList<QString> knownDevices;

    for (const auto &device : deviceInfos)
    {
        if (knownDevices.contains(device.deviceName()))
            continue;
#ifdef Q_OS_LINUX
        else if (!device.deviceName().contains("alsa_output"))
            continue;
#endif

        QString deviceName = device.deviceName();
        audioComboBox->addItem(deviceName, deviceName);
        knownDevices.append(deviceName);
    }
}

void SetupWizard::saveAudioDevice(QString deviceName)
{
    MainWindow *parent = qobject_cast<MainWindow *>(parent_widget);
    parent->appConfig->setValue("Audio", "Device", deviceName);
    parent->appConfig->applyChanges();
}

void SetupWizard::saveNetworkDevice(QString deviceName)
{
    MainWindow *parent = qobject_cast<MainWindow *>(parent_widget);
    parent->appConfig->setValue("Network", "Device", deviceName);
    parent->appConfig->applyChanges();
}

void SetupWizard::addNetworkDevicesToCombobox(QComboBox *comboBox)
{
    const auto interfaces = QNetworkInterface::allInterfaces();
    QList<QString> knownInterfaces;

    foreach (QNetworkInterface interface, interfaces)
    {
        if (knownInterfaces.contains(interface.humanReadableName()))
            continue;

        QString interfaceName = interface.humanReadableName();
        comboBox->addItem(interfaceName, interfaceName);
        knownInterfaces.append(interfaceName);
    }
}

void SetupWizard::setLoadKernelModuleState(int state)
{
    MainWindow *parent = qobject_cast<MainWindow *>(parent_widget);

    parent->appConfig->setValue("General", "LoadModuleOnStart", state == Qt::Checked ? true : false);
    parent->appConfig->applyChanges();
}

void SetupWizard::onPageChanged(int id)
{
    MainWindow *parent = qobject_cast<MainWindow *>(parent_widget);

#ifdef Q_OS_LINUX
    if (id == 2 && parent->appConfig->getValue("General", "LoadModuleOnStart").toBool())
    {
        Linux::loadKernelModule();
        addAudioDevicesToCombobox();
    }
#endif
}
