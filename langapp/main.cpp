#include <QApplication>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include "mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("test");
    db.setPassword("test123");
    bool ok = db.open();
    qDebug() << ok;


    QSqlQuery query;
    auto MakeTable = query.exec("CREATE TABLE Jezyki(id_jez int PRIMARY KEY, nazwa VARCHAR)");
    //auto DeleteTable = query.exec("DROP TABLE Jezyki");
    auto prepare = query.prepare("INSERT INTO Jezyki(id_jez, nazwa)"
                      "VALUES (:id_jez, :nazwa)");
    query.bindValue(":id_jez", 1);
    query.bindValue(":nazwa", "angielski");
    qDebug() << "MakeTable = " << MakeTable;
    //qDebug() << "DeleteTable = " << DeleteTable;
    qDebug() << "prepare = " << prepare;
    QSqlQuery select("SELECT * FROM Jezyki");

    QSqlTableModel test;
    test.setTable("Jezyki");
    test.select();
    QTableView* testView = new QTableView;
    testView->setModel(&test);
    testView->show();


    return a.exec();
}
