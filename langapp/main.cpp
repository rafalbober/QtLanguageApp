#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include <QtSql/QSqlDatabase>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
      db.setHostName("bigblue");
      db.setDatabaseName("flightdb");
      db.setUserName("acarlson");
      db.setPassword("1uTbSbAs");
      bool ok = db.open();
    return a.exec();
}
