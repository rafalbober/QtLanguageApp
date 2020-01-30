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
    Lang->addTransition(ui->CheckWord, SIGNAL(clicked(bool)), Checker);
    Lang->addTransition(ui->PicRec, SIGNAL(clicked(bool)), PicTest);

    PicTest->addTransition(ui->MainMenu_2, SIGNAL(clicked(bool)), Startup);

    Checker->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);
    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);
    Checker->addTransition(wordCmp, SIGNAL(changed(QString)), Edit);

    Edit->addTransition(ui->MainMenu, SIGNAL(clicked(bool)), Startup);

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
    /*lang = "Japan";
    emit langChange(lang);*/
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

void MainWindow::on_jpnMainMenu_clicked(bool checked)
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
