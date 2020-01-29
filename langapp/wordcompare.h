#ifndef WORDCOMPARE_H
#define WORDCOMPARE_H


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <vector>

#include <QObject>


class WordCompare : public QObject
{
    Q_OBJECT
public:
    explicit WordCompare(QObject *parent = nullptr);


public slots:
    void assignValue(QString val);
    void randomMaker();

signals:
    void changed(QString);

private:
    QString lang;
};

#endif // WORDCOMPARE_H
