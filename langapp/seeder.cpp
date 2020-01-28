#include "seeder.h"


Seeder::Seeder()
{
    langs = {"polski", "angielski", "niemiecki"};
    categories = {"zwierzęta"};
    engWords = {"Dog", "Cat", "Beaver"};
    deWords = {"Hund", "Katze", "Biber"};
    plWords = {"Pies", "Kot", "Bóbr"};
}

int Seeder::initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("test");
    db.setUserName("test");
    db.setPassword("test123");
    int ok = db.open();
    return ok;
}

int Seeder::MakeTables()
{
    QSqlQuery query;
    auto languages = query.exec("CREATE TABLE Jezyki(id_jez int PRIMARY KEY, nazwa VARCHAR)");
    auto categories = query.exec("CREATE TABLE Kategorie(id_kat int PRIMARY KEY, nazwa VARCHAR)");
    auto words = query.exec("CREATE TABLE Slowa(id_sl int PRIMARY KEY, pl VARCHAR, ang VARCHAR, niem VARCHAR)");

    return (languages + categories + words);
}

int Seeder::DeleteTables()
{
    QSqlQuery query;
    auto languages = query.exec("DROP TABLE Jezyki");
    auto categories = query.exec("DROP TABLE Kategorie");
    auto words = query.exec("DROP TABLE Slowa");

    return (languages + categories + words);
}

int Seeder::FillLangs()
{
    QSqlQuery query;
    int inserts = 0;

    for (int i = 1; i<=langs.size(); i++)
    {
        query.prepare("INSERT INTO Jezyki(id_jez, nazwa)"
                          "VALUES (:id_jez, :nazwa)");
        query.bindValue(":id_jez", i);
        query.bindValue(":nazwa", langs[i-1]);
        auto fill = query.exec();
        if (fill)
            inserts++;
    }
    return inserts;
}

int Seeder::FillCategories()
{
    QSqlQuery query;
    int inserts = 0;

    for (int i = 1; i<=categories.size(); i++)
    {
        query.prepare("INSERT INTO Kategorie(id_kat, nazwa)"
                          "VALUES (:id_kat, :nazwa)");
        query.bindValue(":id_kat", i);
        query.bindValue(":nazwa", categories[i-1]);

        auto fill = query.exec();

        if (fill)
            inserts++;
    }
    return inserts;
}

int Seeder::FillWords()
{
    QSqlQuery query;
    int inserts = 0;

    for (int i = 1; i<=plWords.size(); i++)
    {
        query.prepare("INSERT INTO Slowa(id_sl, pl, ang, niem)"
                          "VALUES (:id_sl, :pl, :ang, :niem)");
        query.bindValue(":id_sl", i);
        query.bindValue(":pl", plWords[i-1]);
        query.bindValue(":ang", engWords[i-1]);
        query.bindValue(":niem", deWords[i-1]);

        auto fill = query.exec();

        if (fill)
            inserts++;
    }
    return inserts;
}
