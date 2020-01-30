#ifndef WORDCOMPARE_H
#define WORDCOMPARE_H


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <vector>
#include <QObject>
#include <QPixmap>

#include <algorithm>
#include <cctype>
#include <string>


class WordCompare : public QObject
{
    Q_OBJECT
public:
    explicit WordCompare(QObject *parent = nullptr);
    void checkCorrect(QString);

public slots:
    void assignValue(QString val);
    void randomMaker();
    void picRand();
    void selectJpn();
    void checkJpn(QString);

signals:
    void changed(QString);
    void correctWord(QString);
    void incorrectWord(QString);
    void correctPic(QString);
    void incorrectPic(QString);
    void picRanded(QPixmap);
    void jpnRanded(QString);
    void jpnOk(QString);
    void jpnNo(QString);

private:
    QString lang;
    int id;
    QString word;
    int app;
};

#endif // WORDCOMPARE_H
