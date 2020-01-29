#ifndef WORDCOMPARE_H
#define WORDCOMPARE_H


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <vector>
#include <QObject>

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


signals:
    void changed(QString);
    void correct();
    void incorrect();

private:
    QString lang;
    int id;
    QString word;
};

#endif // WORDCOMPARE_H
