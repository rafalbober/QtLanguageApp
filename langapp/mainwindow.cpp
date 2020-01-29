#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStateMachine>
#include <QDebug>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto stateMachine = new QStateMachine(this);

    auto Startup = new QState(stateMachine);
    auto Checker = new QState(stateMachine);
    auto Edit = new QState(stateMachine);
    auto Check = new QState(stateMachine);
    auto Correct = new QState(stateMachine);
    auto Incorrect = new QState(stateMachine);


    Startup->addTransition(ui->CheckWord, SIGNAL(clicked(bool)), Checker);


    Checker->assignProperty(ui->pbCheck, "enabled", false);
    Checker->assignProperty(ui->pbRandom, "enabled", true);
    Checker->assignProperty(ui->pbAnswer, "enabled", false);
    Checker->assignProperty(ui->pbAnswer, "text", "???");
    Checker->assignProperty(ui->text1, "enabled", false);
    Checker->assignProperty(ui->text2, "enabled", false);
    Checker->assignProperty(ui->text1, "placeholderText","Random word");
    Checker->assignProperty(ui->text2, "placeholderText","Your answer");

    Checker->addTransition(ui->pbRandom, SIGNAL(clicked(bool)), Edit);

    Edit->assignProperty(ui->pbCheck, "enabled", true);
    Edit->assignProperty(ui->pbRandom, "enabled", true);
    Edit->assignProperty(ui->pbAnswer, "enabled", false);
    Edit->assignProperty(ui->pbAnswer, "text", "???");
    Edit->assignProperty(ui->text1, "enabled", false);
    Edit->assignProperty(ui->text1, "text", "test");                              // "Losowanie" słowa - prowizorka narazie
    Edit->assignProperty(ui->text2, "enabled", true);
    Edit->assignProperty(ui->text2, "placeholderText","Your answer");

    Edit->addTransition(ui->pbCheck, SIGNAL(clicked(bool)), Check);

    connect(Check, SIGNAL(entered()), this, SLOT(check()));
    Check->addTransition(this, SIGNAL(correct()), Correct);
    Check->addTransition(this, SIGNAL(incorrect()), Incorrect);



    Correct->assignProperty(ui->pbCheck, "enabled", false);
    Correct->assignProperty(ui->pbRandom, "enabled", true);
    Correct->assignProperty(ui->pbAnswer, "enabled", false);
    Correct->assignProperty(ui->pbAnswer, "text", "CORRECT!");
    Correct->assignProperty(ui->text1, "enabled", false);
    Correct->assignProperty(ui->text2, "enabled", true);

    Correct->addTransition(ui->text2, SIGNAL(textChanged(QString)),Edit);
    Correct->addTransition(ui->pbRandom, SIGNAL(clicked(bool)),Edit);


    Incorrect->assignProperty(ui->pbCheck, "enabled", false);
    Incorrect->assignProperty(ui->pbRandom, "enabled", true);
    Incorrect->assignProperty(ui->pbAnswer, "enabled", false);
    Incorrect->assignProperty(ui->pbAnswer, "text", "Incorrect! :C");
    Incorrect->assignProperty(ui->text1, "enabled", false);
    Incorrect->assignProperty(ui->text2, "enabled", true);

    Incorrect->addTransition(ui->text2, SIGNAL(textChanged(QString)),Edit);
    Incorrect->addTransition(ui->pbRandom, SIGNAL(clicked(bool)),Edit);

    stateMachine->setInitialState(Checker);

    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check()
{
    QString s1 = ui->text1->text();
    qDebug() << s1;
    QString s2 = ui->text2->text();
    qDebug() << s2;
    if (s2 == s1) emit correct();
    else emit incorrect();
}

void MainWindow::on_CheckWord_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_MainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
