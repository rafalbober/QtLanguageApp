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
     app = 1;
     emit changed(b);
}

void WordCompare::picRand()
{
    QSqlQuery query;
    QPixmap b;
    QByteArray z;

    query.prepare("select id_sl, image from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    query.exec();
     while (query.next()) {
         id = query.value(0).toInt();
         z = query.value(1).toByteArray();
         b.loadFromData(z,"JPG");
     }

    app = 2;
    emit picRanded(b);
}

void WordCompare::selectJpn()
{
    //qDebug() << "Jpn rand";
    QSqlQuery query;
    query.prepare("select id_sl, Polish, Japan from Slowa WHERE id_sl >= (abs(random()) % (SELECT max(id_sl + 1) FROM Slowa)) limit 1");
    query.exec();
    QString pl;
    QString jpn;

    while (query.next()) {
        id = query.value(0).toInt();
        pl = query.value(1).toString();
        jpn = query.value(2).toString();
        qDebug() << id;
        qDebug() << pl;
        qDebug() << jpn;
    }

    emit jpnRanded(jpn);
}

void WordCompare::checkJpn(QString s)
{
    QSqlQuery query;
    query.prepare("select id_sl, Polish from Slowa WHERE id_sl = :id)");
    query.bindValue(":id", id);
    query.exec();
    QString pl;
    while (query.next()) {
        pl = query.value(0).toString();
        qDebug() << pl;
    }
    if( QString::compare(s, pl, Qt::CaseInsensitive) ) {
        emit jpnOk("Brawo!");
    }
    else {
        emit jpnNo("Nie!");
    }
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
        if (app == 1)
            emit correctWord("Brawo!");
        if (app == 2)
            emit correctPic("Brawo!");
    }
    else
    {
        if (app == 1)
            emit incorrectWord("Nie!");
        if (app == 2)
            emit incorrectPic("Nie!");
    }
}

void WordCompare::assignValue(QString val)
{
    this->lang = val;
}
