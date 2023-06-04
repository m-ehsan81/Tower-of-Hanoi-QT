#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Splash Screen
    QSplashScreen Splsh = new QSplashScreen;
    Splsh.setPixmap(QPixmap("C:/Users/Lenovo/Desktop/splash_hanoi.jpg"));
    Splsh.show();

    MainWindow w;
    QTimer::singleShot(2000,&Splsh,SLOT(close()));
    QTimer::singleShot(2000,&w,SLOT(show()));
  //  w.show();
    return a.exec();
}
