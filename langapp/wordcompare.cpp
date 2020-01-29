#include "wordcompare.h"

WordCompare::WordCompare(QObject *parent) : QObject(parent)
{

}

void WordCompare::randomMaker()
{
    QSqlQuery query;
    QString b;

    /*
    if(lang == "English")
        query.prepare("select id_sl, English from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    if(lang == "Deutsch")
        query.prepare("select id_sl, Deutsch from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    if(lang == "Japan")
        query.prepare("select id_sl, Japan from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    */
    query.prepare("select id_sl, Polish from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    query.exec();
     while (query.next()) {
         id = query.value(0).toInt();
         b = query.value(1).toString();
         qDebug() <<  b;
     }

     emit changed(b);
}

void WordCompare::checkCorrect(QString val)
{
    QSqlQuery query;
    QString b;
    if(lang == "English")
        query.prepare("select English from Slowa WHERE id_sl = :id ");
    if(lang == "Deutsch")
        query.prepare("select Deutsch from Slowa WHERE id_sl = :id ");
    if(lang == "Japan")
        query.prepare("select Japan from Slowa WHERE id_sl = :id ");
    query.bindValue(":id", id);

    query.exec();
    while (query.next()) {
        b = query.value(0).toString();
        qDebug() <<  b;
    }
    qDebug()<<val;

    if(!QString::compare(b, val, Qt::CaseInsensitive))
    {
        emit correct();
    }
    else
    {
        emit incorrect();
    }
}

void WordCompare::assignValue(QString val)
{
    this->lang = val;
}
