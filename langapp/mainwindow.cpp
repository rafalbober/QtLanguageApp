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
    auto PicTest = new QState(stateMachine);
    auto PicRand = new QState(stateMachine);
    auto Japan = new QState(stateMachine);
    auto JapanRand = new QState(stateMachine);


    //-----------------------------CONNECTS-------------------------------------------

    connect(this, SIGNAL(langChange(QString)), wordCmp, SLOT(assignValue(QString)));
    connect(ui->pbRandom, SIGNAL(clicked()), wordCmp, SLOT(randomMaker()));
    connect(ui->picBt, SIGNAL(clicked()), wordCmp, SLOT(picRand()));
    connect(wordCmp,SIGNAL(picRanded(QPixmap)),this,SLOT(picDisplay(QPixmap)));
    connect(wordCmp,SIGNAL(changed(QString)),this,SLOT(assignValue(QString)));
    connect(wordCmp,SIGNAL(changed(QString)),ui->ShowText,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(correctPic(QString)),ui->picCorr,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(incorrectPic(QString)),ui->picCorr,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(correctWord(QString)),ui->pbAnswer,SLOT(setText(QString)));
    connect(wordCmp,SIGNAL(incorrectWord(QString)),ui->pbAnswer,SLOT(setText(QString)));

    // japanese
    connect(wordCmp, SIGNAL(jpnRanded(QString)), ui->jpnWord, SLOT(setText(QString)));
    connect(wordCmp, SIGNAL(jpnOk(QString)), ui->jpnRes, SLOT(setText(QString)));
    connect(wordCmp, SIGNAL(jpnNo(QString)), ui->jpnRes, SLOT(setText(QString)));

    //---------------------------TRANSITIONS--------------------------------------

    Startup->addTransition(this, SIGNAL(langChange(QString)), Lang);
    Startup->addTransition(ui->JapanBt, SIGNAL(clicked(bool)), Japan);
    Lang->addTransition(ui->JapanBt, SIGNAL(clicked(bool)), Japan);
    Lang->addTransition(ui->CheckWord, SIGNAL(clicked(bool)), Checker);
    Lang->addTransition(ui->PicRec, SIGNAL(clicked(bool)), PicTest);

    PicTest->addTransition(ui->MainMenu_2, SIGNAL(clicked(bool)), Startup);
    PicTest->addTransition(ui->picBt, SIGNAL(clicked(bool)), PicRand);
    PicRand->addTransition(ui->MainMenu_2, SIGNAL(clicked(bool)), Startup);


    Checker->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);

    Edit->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);

    Japan->addTransition(ui->jpnMainMenu, SIGNAL(clicked(bool)), Startup);
    Japan->addTransition(ui->jpnRand, SIGNAL(clicked(bool)), JapanRand);
    JapanRand->addTransition(ui->jpnMainMenu, SIGNAL(clicked(bool)), Startup);

    //-----------------------ASSIGN PROPERTY----------------------------------
    Startup->assignProperty(ui->stackedWidget,"currentIndex", 0);
    Startup->assignProperty(ui->CheckWord, "enabled", false);
    Startup->assignProperty(ui->PicRec, "enabled", false);
    Startup->assignProperty(ui->JapanBt, "enabled", true);
    Lang->assignProperty(ui->CheckWord, "enabled", true);
    Lang->assignProperty(ui->PicRec, "enabled", true);

    Checker->assignProperty(ui->pbCheck, "enabled", false);
    Checker->assignProperty(ui->pbRandom, "enabled", true);
    Checker->assignProperty(ui->pbAnswer, "enabled", false);
    Checker->assignProperty(ui->ShowText, "enabled", false);
    Checker->assignProperty(ui->TypeText, "enabled", false);
    Checker->assignProperty(ui->ShowText, "text", "Losowe słowo");
    Checker->assignProperty(ui->TypeText, "placeholderText","Twoja odpowiedź");

    Edit->assignProperty(ui->pbCheck, "enabled", true);
    Edit->assignProperty(ui->TypeText, "enabled", true);
    Edit->assignProperty(ui->TypeText, "placeholderText","Twoja odpowiedź");

    PicTest->assignProperty(ui->picCorr, "text", "");
    PicTest->assignProperty(ui->picText, "enabled", false);
    PicTest->assignProperty(ui->picCheck, "enabled", false);
    PicRand->assignProperty(ui->picText, "enabled", true);
    PicRand->assignProperty(ui->picCheck, "enabled", true);

    Japan->assignProperty(ui->stackedWidget,"currentIndex", 3);
    Japan->assignProperty(ui->jpnWord, "text", "");
    Japan->assignProperty(ui->jpnRes, "text", "");
    Japan->assignProperty(ui->jpnCheck, "enabled", false);
    Japan->assignProperty(ui->jpnTranslate, "enabled", false);

    JapanRand->assignProperty(ui->jpnCheck, "enabled", true);
    JapanRand->assignProperty(ui->jpnTranslate, "enabled", true);

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

void MainWindow::picDisplay(QPixmap pixmap)
{
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setScaledContents(true);
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
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pbCheck_clicked()
{
    wordCmp->checkCorrect(ui->TypeText->text());
}


void MainWindow::on_PicRec_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_MainMenu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_picCheck_clicked()
{
    wordCmp->checkCorrect(ui->picText->text());
}

void MainWindow::on_jpnMainMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_jpnRand_clicked()
{
    ui->jpnRes->setText("");
    wordCmp->selectJpn();
}

void MainWindow::on_jpnCheck_clicked()
{
    wordCmp->checkJpn(ui->jpnTranslate->text());
}
