#include "wordcompare.h"

WordCompare::WordCompare(QObject *parent) : QObject(parent)
{

}

void WordCompare::randomMaker()
{
    QSqlQuery query;
    QString b = lang;
    /*
    query.prepare("select :id from Slowa order by rand() limit 1");
    query.bindValue(":id", lang);
    query.exec();
     while (query.next()) {
         b = query.value(0).toString();
         qDebug() << "pierdolony laglicz "<< b;
     }
     */
     qDebug() << "pierdolony laglicz "<< b;

    emit changed(b);
}

void WordCompare::assignValue(QString val)
{
    this->lang = val;
}
