#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


public slots:
    void check();


private slots:
    void on_CheckWord_clicked();

    void on_MainMenu_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
