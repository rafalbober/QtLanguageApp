#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wordcompare.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void correct();
    void incorrect();
    void langChange(QString val);


public slots:
    void assignValue(QString val);


private slots:
    void on_CheckWord_clicked();
    void on_MainMenu_clicked();
    void on_EnglishBt_clicked();
    void on_DeutschBt_clicked();
    void on_JapanBt_clicked();
    void on_pbCheck_clicked();

    void on_pushButton_clicked(bool checked);

    void on_PicRec_clicked(bool checked);

    void on_MainMenu_2_clicked();

    void on_imageLabel_linkHovered(const QString &link);

private:
    Ui::MainWindow *ui;
    WordCompare* wordCmp;
    QString word;
    QString lang;

};

#endif // MAINWINDOW_H
