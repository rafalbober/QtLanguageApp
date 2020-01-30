#ifndef SEEDER_H
#define SEEDER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <vector>
#include <QtSql>
#include <QtWidgets>

class Seeder
{
public:
    Seeder();
    QSqlDatabase initDb();
    int MakeTables();
    int DeleteTables();
    int FillLangs();
    int FillCategories();
    int FillWords();
private:
    std::vector<QString> langs;
    std::vector<QString> categories;
    std::vector<QString> plWords;
    std::vector<QString> engWords;
    std::vector<QString> deWords;
    std::vector<QString> imageNames;

};

#endif // SEEDER_H
