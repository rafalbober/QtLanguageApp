#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStateMachine>
#include <QDebug>
#include <QStackedWidget>
#include <QResource>

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
    auto Correct = new QState(stateMachine);
    auto Incorrect = new QState(stateMachine);

    //-----------------------------CONNECTS-------------------------------------------

    connect(this, SIGNAL(langChange(QString)), wordCmp, SLOT(assignValue(QString)));
    connect(ui->pbRandom, SIGNAL(clicked()), wordCmp, SLOT(randomMaker()));
    connect(wordCmp,SIGNAL(changed(QString)),this,SLOT(assignValue(QString)));
    connect(wordCmp,SIGNAL(changed(QString)),ui->ShowText,SLOT(setText(QString)));

    //---------------------------TRANSITIONS--------------------------------------

    Startup->addTransition(this, SIGNAL(langChange(QString)), Lang);
    Lang->addTransition(ui->CheckWord, SIGNAL(clicked(bool)), Checker);

    Checker->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);

    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);

    Edit->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Edit->addTransition(wordCmp,SIGNAL(correct()), Correct);
    Edit->addTransition(wordCmp,SIGNAL(incorrect()), Incorrect);

    Correct->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Correct->addTransition(ui->TypeText, SIGNAL(textChanged(QString)),Edit);
    Correct->addTransition(ui->pbRandom, SIGNAL(clicked(bool)),Edit);

    Incorrect->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Incorrect->addTransition(ui->TypeText, SIGNAL(textChanged(QString)),Edit);
    Incorrect->addTransition(ui->pbRandom, SIGNAL(clicked(bool)),Edit);


    //-----------------------ASSIGN PROPERTY----------------------------------
    Startup->assignProperty(ui->stackedWidget,"currentIndex", 0);
    Startup->assignProperty(ui->CheckWord, "enabled", false);
    Startup->assignProperty(ui->JapanBt, "enabled", false);
    Lang->assignProperty(ui->CheckWord, "enabled", true);

    Checker->assignProperty(ui->pbCheck, "enabled", false);
    Checker->assignProperty(ui->pbRandom, "enabled", true);
    Checker->assignProperty(ui->pbAnswer, "enabled", false);
    Checker->assignProperty(ui->pbAnswer, "text", "???");
    Checker->assignProperty(ui->ShowText, "enabled", false);
    Checker->assignProperty(ui->TypeText, "enabled", false);
    Checker->assignProperty(ui->ShowText, "text","Random word");
    Checker->assignProperty(ui->TypeText, "placeholderText","Your answer");

    Edit->assignProperty(ui->pbCheck, "enabled", true);
    Edit->assignProperty(ui->pbRandom, "enabled", true);
    Edit->assignProperty(ui->pbAnswer, "enabled", false);
    Edit->assignProperty(ui->pbAnswer, "text", "???");
    Edit->assignProperty(ui->ShowText, "enabled", false);
    Edit->assignProperty(ui->TypeText, "enabled", true);
    Edit->assignProperty(ui->TypeText, "placeholderText","Your answer");

    Correct->assignProperty(ui->pbCheck, "enabled", false);
    Correct->assignProperty(ui->pbRandom, "enabled", true);
    Correct->assignProperty(ui->pbAnswer, "enabled", false);
    Correct->assignProperty(ui->pbAnswer, "text", "CORRECT!");
    Correct->assignProperty(ui->ShowText, "enabled", false);
    Correct->assignProperty(ui->TypeText, "enabled", true);

    Incorrect->assignProperty(ui->pbCheck, "enabled", true);
    Incorrect->assignProperty(ui->pbRandom, "enabled", true);
    Incorrect->assignProperty(ui->pbAnswer, "enabled", false);
    Incorrect->assignProperty(ui->pbAnswer, "text", "Incorrect! :C\nTry Again");
    Incorrect->assignProperty(ui->ShowText, "enabled", false);
    Incorrect->assignProperty(ui->TypeText, "enabled", true);

    //-----------------------------------------------------------------------

    stateMachine->setInitialState(Startup);

    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::assignValue(QString val)
{
    word = val;
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

void MainWindow::on_pbCheck_clicked()
{
    wordCmp->checkCorrect(ui->TypeText->text());
}


void MainWindow::on_PicRec_clicked(bool checked)
{
    ui->stackedWidget->setCurrentIndex(2);
    QPixmap pixmap(":/imgs/images.jpeg");
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setScaledContents(true);
}

void MainWindow::on_MainMenu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_imageLabel_linkHovered(const QString &link)
{

}
