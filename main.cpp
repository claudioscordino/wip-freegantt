#include "mainwindow.hpp"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/gantt-hi.png"));
    //splash->resize(184, 300);
    splash->show();
    Qt::Alignment bottomCenter = Qt::AlignCenter| Qt::AlignBottom;
    splash->showMessage(QObject::tr("Starting application..."), bottomCenter, Qt::white);

    MainWindow w;
    splash->finish(&w);
    delete splash;
    w.show();

    return a.exec();
}
