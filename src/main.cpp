#include "src/ui/MainWindow/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setApplicationName("pl.grzybdev.openmic.server");
	QCoreApplication::setApplicationVersion(APP_VERSION);
	QCoreApplication::setOrganizationDomain("grzybdev.github.io");
	QCoreApplication::setOrganizationName("GrzybDev");

	QTranslator translator;
	const QStringList uiLanguages = QLocale::system().uiLanguages();
	for (const QString &locale : uiLanguages)
	{
		const QString baseName = "OpenMic_Server_" + QLocale(locale).name();
		if (translator.load(":/i18n/" + baseName))
		{
			translator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
			QApplication::installTranslator(&translator);
			break;
		}
	}

	MainWindow w;
	return QApplication::exec();
}
