#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStateMachine>
#include <QDebug>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    wordCmp = new WordCompare();
    ui->setupUi(this);

    auto stateMachine = new QStateMachine(this);

    auto Startup = new QState(stateMachine);
    auto Lang = new QState(stateMachine);
    auto Checker = new QState(stateMachine);
    auto Edit = new QState(stateMachine);
    auto Check = new QState(stateMachine);
    auto Correct = new QState(stateMachine);
    auto Incorrect = new QState(stateMachine);



    Checker->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Correct->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Incorrect->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Edit->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);

    Startup->assignProperty(ui->CheckWord, "enabled", false);
    connect(this, SIGNAL(langChange(QString)), wordCmp, SLOT(assignValue(QString)));
    Startup->addTransition(this, SIGNAL(langChange(QString)), Lang);
    Lang->assignProperty(ui->CheckWord, "enabled", true);
    Lang->addTransition(ui->CheckWord, SIGNAL(clicked(bool)), Checker);


    Checker->assignProperty(ui->pbCheck, "enabled", false);
    Checker->assignProperty(ui->pbRandom, "enabled", true);
    Checker->assignProperty(ui->pbAnswer, "enabled", false);
    Checker->assignProperty(ui->pbAnswer, "text", "???");
    Checker->assignProperty(ui->text1, "enabled", false);
    Checker->assignProperty(ui->text2, "enabled", false);
    Checker->assignProperty(ui->text1, "text","Random word");
    Checker->assignProperty(ui->text2, "placeholderText","Your answer");


    connect(ui->pbRandom, SIGNAL(clicked()), wordCmp, SLOT(randomMaker()));
    connect(wordCmp,SIGNAL(changed(QString)),this,SLOT(assignValue(QString)));
    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);
    connect(wordCmp,SIGNAL(changed(QString)),ui->text1,SLOT(setText(QString)));

    Edit->assignProperty(ui->pbCheck, "enabled", true);
    Edit->assignProperty(ui->pbRandom, "enabled", true);
    Edit->assignProperty(ui->pbAnswer, "enabled", false);
    Edit->assignProperty(ui->pbAnswer, "text", "???");
    Edit->assignProperty(ui->text1, "enabled", false);
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

    stateMachine->setInitialState(Startup);

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

void MainWindow::assignValue(QString val)
{
    word = val;
    qDebug() << word;
}

void MainWindow::on_CheckWord_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_MainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_EnglishBt_clicked()
{
    lang = "English";
    emit langChange(lang);
}


void MainWindow::on_DeutschBt_clicked()
{
    lang = "Deutsch";
    emit langChange(lang);
}

void MainWindow::on_JapanBt_clicked()
{
    lang = "Japan";
    emit langChange(lang);
}
