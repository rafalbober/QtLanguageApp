#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "seeder.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>

int main(int argc, char* argv[])
{
    // Show window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Seeder seeder{};
    int db = seeder.initDb();
    int dels = seeder.DeleteTables();
    int tables = seeder.MakeTables();
    int langs = seeder.FillLangs();
    //int ctgs = seeder.FillCategories();
    int words = seeder.FillWords();

    qDebug() << "Deletions: " << dels;
    qDebug() << "Table creations: " << tables;
    qDebug() << "Language insertions: " << langs;
    qDebug() << "Words added: " << words;

    // Table view
    /*QSqlTableModel test;
    test.setTable("Jezyki");
    test.select();
    QTableView* testView = new QTableView;
    testView->setModel(&test);
    testView->show();*/


    return a.exec();
}
