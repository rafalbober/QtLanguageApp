/*#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}*/

#include <QApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QNetworkAccessManager* qnam = new QNetworkAccessManager();
    QNetworkReply* rep = qnam->get(QNetworkRequest(QUrl("https://translate.google.com/?hl=pl#view=home&op=translate&sl=en&tl=pl&text=great")));
    qDebug() << rep;
    QString result = QVariant(rep->readAll()).toString();
    qDebug() << result;
    qnam->deleteLater();
    return a.exec();
}
