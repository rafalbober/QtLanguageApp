#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "seeder.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QtSql>
#include <QtWidgets>

int main(int argc, char* argv[])
{
    // Show window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Create connection and seed database
    Seeder seeder{};
    QSqlDatabase db = seeder.initDb();
    int dels = seeder.DeleteTables();
    int tables = seeder.MakeTables();
    int langs = seeder.FillLangs();
    int ctgs = seeder.FillCategories();
    int words = seeder.FillWords();

    // Log operations results
    qDebug() << "Database started: " << db;
    qDebug() << "Deletions: " << dels;
    qDebug() << "Table creations: " << tables;
    qDebug() << "Language insertions: " << langs;
    qDebug() << "Categories added: " << ctgs;
    qDebug() << "Words added: " << words;

    /* TABLE MODELS */

    /*// Languages
    QSqlTableModel langsTable;
    langsTable.setTable("Jezyki");
    langsTable.select();
    QTableView* langsTableView = new QTableView;
    langsTableView->setModel(&langsTable);
    langsTableView->show();

    // Words
    QSqlTableModel wordsTable;
    wordsTable.setTable("Slowa");
    wordsTable.select();
    QTableView* wordsTableView = new QTableView;
    wordsTableView->setModel(&wordsTable);
    wordsTableView->show();

    // Categories
    QSqlTableModel ctgsTable;
    ctgsTable.setTable("Kategorie");
    ctgsTable.select();
    QTableView* ctgsTableView = new QTableView;
    ctgsTableView->setModel(&ctgsTable);
    ctgsTableView->show();*/


    return a.exec();
}

