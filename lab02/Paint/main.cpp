#include "Paint.h"
#include <QGuiApplication>
#include <QScreen>
#include <QTableWidget>
#include <QWindow>
#include <QtWidgets/QApplication>
#include <QDebug>
	
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	Paint window;
	window.showMaximized();

	return app.exec();
}
