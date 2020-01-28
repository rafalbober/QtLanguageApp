#include "seeder.h"


Seeder::Seeder()
{
    /*engWords.push_back("Dog"); engWords.push_back("Cat"); engWords.push_back("Beaver");
    deWords.push_back("Hund"); deWords.push_back("Katze"); deWords.push_back("Biber");
    plWords.push_back("")*/
    engWords = {"Dog", "Cat", "Beaver"};
    deWords = {"Hund", "Katze", "Biber"};
    plWords = {"Pies", "Kot", "Bober"};
}

int Seeder::MakeTables()
{
    QSqlQuery query;
    auto languages = query.exec("CREATE TABLE Jezyki(id_jez int PRIMARY KEY, nazwa VARCHAR)");
    auto categories = query.exec("CREATE TABLE Kategorie(id_kat int PRIMARY KEY, nazwa VARCHAR)");
    auto words = query.exec("CREATE TABLE Slowa(id_sl int PRIMARY KEY, slowo VARCHAR)");

    query.exec();

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

int Seeder::FillTables()
{
    QSqlQuery query;
    auto fillLangs = query.prepare("INSERT INTO Jezyki(id_jez, nazwa)"
                      "VALUES (:id_jez, :nazwa)");
    query.bindValue(":id_jez", 1);
    query.bindValue(":nazwa", "angielski");
}
