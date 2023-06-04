#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QProcess"
#include "QTimer"
#include "QDateTime"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Menu BackGround Image
    QPixmap BackGround("C:/Users/Lenovo/Desktop/back.jpg");
    BackGround = BackGround.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Window,BackGround);
    this->setPalette(Palette);

    //Hide All Tool For Menu
    ui->pushButton1->hide();     ui->pushButton2->hide();     ui->pushButton3->hide();     ui->pushButton4->hide();
    ui->pushButtonA->hide();   ui->pushButtonB->hide();     ui->pushButtonC->hide();
    ui->pushButton_Timer->hide();
    ui->label_Count->hide();     ui->label_Timer->hide();    ui->label_Hint->hide();
    ui->toolBar->hide();

    // menu Buttons
    Start = new QPushButton("Start",this);
    Start->setGeometry(125,100,650,70);
    connect(Start,&QPushButton::released,this,&MainWindow::StartButton);

    Help = new QPushButton("How To Play",this);
    Help->setGeometry(125,180,325,70);
    connect(Help,&QPushButton::released,this,&MainWindow::HelpButton);

    Quit = new QPushButton("Exit",this);
    Quit->setGeometry(450,180,325,70);
    connect(Quit,&QPushButton::released,this,&MainWindow::QuitButton);

    Start->setStyleSheet("background-color : #f64001");
    Help->setStyleSheet("background-color : #4493a0");
    Quit->setStyleSheet("background-color : #4493a0");   
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Menu Start Button Function
void MainWindow::StartButton(){

    //MainWindow Background
    QPixmap BackGround("C:/Users/Lenovo/Desktop/th.jpg");
    BackGround = BackGround.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette Palette;
    Palette.setBrush(QPalette::Window,BackGround);
    this->setPalette(Palette);

    //Show All Buttons After Start Button Clicked
    Start->hide();    Help->hide();     Quit->hide();
    ui->pushButton1->setStyleSheet("background-color : #f64001");
    ui->pushButton2->setStyleSheet("background-color : #4493a0");
    ui->pushButton3->setStyleSheet("background-color : #f64001");
    ui->pushButton4->setStyleSheet("background-color : #4493a0");
    ui->pushButtonA->setStyleSheet("background-color : #bc8d5b; color : #532f09");
    ui->pushButtonB->setStyleSheet("background-color : #bc8d5b; color : #532f09");
    ui->pushButtonC->setStyleSheet("background-color : #bc8d5b; color : #532f09");
    ui->pushButton_Timer->setStyleSheet("background-color : #bc8d5b; color : #532f09");
    ui->toolBar->setStyleSheet("color : #532f09;");

    ui->pushButton1->show();     ui->pushButton2->show();     ui->pushButton3->show();     ui->pushButton4->show();
    ui->pushButtonA->show();   ui->pushButtonB->show();     ui->pushButtonC->show();
    ui->pushButton_Timer->show();
    ui->label_Count->show();   ui->label_Timer->show();   ui->label_Hint->show();
    ui->toolBar->show();

    //Disable 1 to 4 Buttons For First Time
    ui->pushButton1->setEnabled(activation1);
    ui->pushButton2->setEnabled(activation2);
    ui->pushButton3->setEnabled(activation3);
    ui->pushButton4->setEnabled(activation4);

    //Fix Button Size In All Layout
    ButtonSize();

    //Make Timer For Game
    Time.setHMS(0,1,30);
    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(UpdateTimer()));
}

//Menu Help Button Function
void MainWindow::HelpButton(){

    QMessageBox::information(this,"GAME TUTORIAL","In This Game You Must Move All Buttons In Tower A , In The Same Order To The Tower C \n"
                                                    "There Are Some Rules For Game : \n"
                                                    " -You Can't Take Out Button Under The Other \n"
                                                    " -You Can't Move Bigger Button On Top Of Smaller One \n"
                                                    " -You Have 90 Seconds To Complete The Game & If You Can't Make It Under A Minute You Lose \n"
                                                    "For Playing The Gmae Fist You Must Select Destination Tower & If There Is Any Selectable Button \n"
                                                    "From 1 to 4 They Become Active & You Can Select Them & If No Button Is Selectable You Must Choose \n"
                                                    "Another Tower");
}

//Menu Quit Button Function
void MainWindow::QuitButton(){

    QMessageBox MsgBox;
    MsgBox.setWindowTitle("Exit");
    MsgBox.setText("Are You Sure ?");
    MsgBox.setIcon(QMessageBox::Warning);
    MsgBox.setStandardButtons(QMessageBox::Yes);
    MsgBox.addButton(QMessageBox::No);
    MsgBox.setDefaultButton(QMessageBox::No);

    if(MsgBox.exec() == QMessageBox::Yes){

        QCoreApplication::quit();
    }
}

//Timer Function
void MainWindow::UpdateTimer(){

    //Its Countdown , Each Second Will Minus One Second From Timer
    Time =Time.addSecs(-1);
    ui->label_Timer->setText(Time.toString(" mm : ss"));

    CheckLoose();
}

//Button 1 Activate Function
void MainWindow::Activate1(){

    //Each Layout Get Index & When Its 0 Activate The Button && Check Valid Destination Tower
    if(ui->VL1->indexOf(ui->pushButton1)==0 && (CheckTowerB || CheckTowerC)){

        activation1 = true;
        ui->pushButton1->setEnabled(activation1);
        return;
    }
    else if(ui->VL2->indexOf(ui->pushButton1)==0 && (CheckTowerA|| CheckTowerC)){

        activation1 = true;
        ui->pushButton1->setEnabled(activation1);
        return;
    }
    else if(ui->VL3->indexOf(ui->pushButton1)==0 && (CheckTowerA || CheckTowerB)){

        activation1 = true;
        ui->pushButton1->setEnabled(activation1);
        return;
    }
    else{
        activation1 = false;
        ui->pushButton1->setEnabled(activation1);
        return;
    }
}

//Button 2 Activate Function
void MainWindow::Activate2(){

    CanClick1();

    //Each Layout Get Index & When Its 0 Activate The Button && Check Valid Destination Tower && Check If Button 1 Its Not In Tower
    if((ui->VL1->indexOf(ui->pushButton2)==0) && (CheckTowerB && ClickA2)){

        activation2 = true;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
    else if((ui->VL1->indexOf(ui->pushButton2)==0) && (CheckTowerC && ClickA3)){

        activation2 = true;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
    else if((ui->VL2->indexOf(ui->pushButton2)==0) && (CheckTowerA && ClickA1)){

        activation2 = true;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
    else if((ui->VL2->indexOf(ui->pushButton2)==0) && (CheckTowerC && ClickA3)){

        activation2 = true;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
    else if((ui->VL3->indexOf(ui->pushButton2)==0) && (CheckTowerB && ClickA2)){

        activation2 = true;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
    else if((ui->VL3->indexOf(ui->pushButton2)==0) && (CheckTowerA && ClickA1)){

        activation2 = true;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
    else{
        activation2 = false;
        ui->pushButton2->setEnabled(activation2);
        return;
    }
}

//Button 3 Activate Function
void MainWindow::Activate3(){

    CanClick1();  CanClick2();

    //Each Layout Get Index & When Its 0 Activate The Button && Check Valid Destination Tower && Check If Button 1 or 2 Are Not In Tower
    if((ui->VL1->indexOf(ui->pushButton3)==0) && (CheckTowerB && ClickA2 && ClickB2)){

        activation3 = true;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
    else if((ui->VL1->indexOf(ui->pushButton3)==0) && (CheckTowerC && ClickA3 && ClickB3)){

        activation3 = true;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
    else if((ui->VL2->indexOf(ui->pushButton3)==0) && (CheckTowerA && ClickA1 && ClickB1)){

        activation3 = true;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
    else if((ui->VL2->indexOf(ui->pushButton3)==0) && (CheckTowerC && ClickA3 && ClickB3)){

        activation3 = true;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
    else if((ui->VL3->indexOf(ui->pushButton3)==0) && (CheckTowerB && ClickA2 && ClickB2)){

        activation3 = true;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
    else if((ui->VL3->indexOf(ui->pushButton3)==0) && (CheckTowerA && ClickA1 && ClickB1)){

        activation3 = true;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
    else{
        activation3 = false;
        ui->pushButton3->setEnabled(activation3);
        return;
    }
}

//Button 4 Activate Function
void MainWindow::Activate4(){

    CanClick1();  CanClick2();  CanClick3();

    //Each Layout Get Index & When Its 0 Activate The Button && Check Valid Destination Tower && Check If Button 1 or 2 or 3 Are Not In Tower
    if((ui->VL1->indexOf(ui->pushButton4)==0) && (CheckTowerB && ClickA2 && ClickB2 && ClickC2)){

        activation4 = true;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
    else if((ui->VL1->indexOf(ui->pushButton4)==0) && (CheckTowerC && ClickA3 && ClickB3 && ClickC3)){

        activation4 = true;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
    else if((ui->VL2->indexOf(ui->pushButton4)==0) && (CheckTowerA && ClickA1 && ClickB1 && ClickC1)){

        activation4 = true;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
    else if((ui->VL2->indexOf(ui->pushButton4)==0) && (CheckTowerC && ClickA3 && ClickB3 && ClickC3)){

        activation4 = true;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
    else if((ui->VL3->indexOf(ui->pushButton4)==0) && (CheckTowerB && ClickA2 && ClickB2 && ClickC2)){

        activation4 = true;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
    else if((ui->VL3->indexOf(ui->pushButton4)==0) && (CheckTowerA && ClickA1 && ClickB1 && ClickC1)){

        activation4 = true;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
    else{
        activation4 = false;
        ui->pushButton4->setEnabled(activation4);
        return;
    }
}

//Function To Make Bigger Button Unable To Come On Button 1
void MainWindow::CanClick1(){

    //Each Layout Get Index & When Its 0 Make Bigger Button Unable To Come on It & Make Two Other Tower Click Enable
    if(ui->VL1->indexOf(ui->pushButton1) == 0){

        ClickA1 = false;
        ClickA2 = ClickA3 = true;
        return;
    }
    else if(ui->VL2->indexOf(ui->pushButton1) == 0 ){

        ClickA2 = false;
        ClickA1 = ClickA3 = true;
        return;
    }
    else if(ui->VL3->indexOf(ui->pushButton1) == 0 ){

        ClickA3 = false;
        ClickA1 = ClickA2 = true;
        return;
    }
}

//Function To Make Bigger Button Unable To Come On Button 2
void MainWindow::CanClick2(){

    //Each Layout Get Index & When Its 0 Make Bigger Button Unable To Come on It & Make Two Other Tower Click Enable
    if(ui->VL1->indexOf(ui->pushButton2) == 0 ){

        ClickB1 = false;
        ClickB2 = ClickB3 = true;
        return;
    }
    else if(ui->VL2->indexOf(ui->pushButton2) == 0 ){

        ClickB2 = false;
        ClickB1 = ClickB3 = true;
        return;
    }
    else if(ui->VL3->indexOf(ui->pushButton2) == 0 ){

        ClickB3 = false;
        ClickB1 = ClickB2 = true;
        return;
    }
}

//Function To Make Bigger Button Unable To Come On Button 2
void MainWindow::CanClick3(){

    //Each Layout Get Index & When Its 0 Make Bigger Button Unable To Come on It & Make Two Other Tower Click Enable
    if(ui->VL1->indexOf(ui->pushButton3) == 0){

        ClickC1 = false;
        ClickC2 = ClickC3 = true;
        return;
    }
    else if(ui->VL2->indexOf(ui->pushButton3) == 0){

        ClickC2 = false;
        ClickC1 = ClickC3 = true;
        return;
    }
    else if(ui->VL3->indexOf(ui->pushButton3) == 0){

        ClickC3 = false;
        ClickC1 = ClickC2 = true;
        return;
    }
}

//Function To Check If User Have Won
void MainWindow::CheckWin(){

    CountMove();
    QString Count = QString::number(Counter);

    //If Button Order In Tower A Comes In Tower C User Wins
    if((ui->VL3->indexOf(ui->pushButton1)==0)&&(ui->VL3->indexOf(ui->pushButton2)==1)&&
        (ui->VL3->indexOf(ui->pushButton3)==2)&&(ui->VL3->indexOf(ui->pushButton4)==3)){

        Timer->stop();
        StopStart = true;

        QMessageBox WinMsg;
        WinMsg.setWindowTitle("Win");
        WinMsg.setText("You Have Won The Game With  " + Count + "  Moves");
        WinMsg.setStandardButtons(QMessageBox::Close);
        WinMsg.addButton(QMessageBox::Reset);
        WinMsg.setDefaultButton(QMessageBox::Reset);

        if(WinMsg.exec() ==  QMessageBox::Close){

            QCoreApplication::quit();
        }
        else{

            ResetGame();
        }
    }
}

//Function To Check If Time Is Up
void MainWindow::CheckLoose(){

    //If Timer Reach 90 Seconds User Will Loose
    if(Time.minute() == 0 && Time.second() == 0){

        QMessageBox LosMsg;
        LosMsg.setWindowTitle("Loose");
        LosMsg.setText("You Didn't Complete The Game In Given Time");
        LosMsg.setIcon(QMessageBox::Warning);
        LosMsg.setStandardButtons(QMessageBox::Close);
        LosMsg.addButton(QMessageBox::Reset);
        LosMsg.setDefaultButton(QMessageBox::Reset);

        if(LosMsg.exec() ==  QMessageBox::Close){
            QCoreApplication::quit();
        }else{

            ResetGame();
        }
    }
}

//Button 1 Click Function
void MainWindow::on_pushButton1_clicked()
{
    //Check Destination Tower & Move Button To The Tower
    if(CheckTowerA){

        ui->VL1->insertWidget(0,ui->pushButton1);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerB){

        ui->VL2->insertWidget(0,ui->pushButton1);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerC){

        ui->VL3->insertWidget(0,ui->pushButton1);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    Activate1();  Activate2();  Activate3();  Activate4();

    ButtonSize();

    Counter++;
    CountMove();

    CheckWin();

    ui->label_Hint->setText("Choose     Tower");
}

//Button 2 Click Function
void MainWindow::on_pushButton2_clicked()
{
    //Check Destination Tower & Move Button To The Tower
    if(CheckTowerA){

        ui->VL1->insertWidget(0,ui->pushButton2);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerB){

        ui->VL2->insertWidget(0,ui->pushButton2);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerC){

        ui->VL3->insertWidget(0,ui->pushButton2);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    Activate1();  Activate2();  Activate3();  Activate4();

    ButtonSize();

    Counter++;
    CountMove();

    CheckWin();

    ui->label_Hint->setText("Choose     Tower");
}

//Button 3 Click Function
void MainWindow::on_pushButton3_clicked()
{
    //Check Destination Tower & Move Button To The Tower
    if(CheckTowerA){

        ui->VL1->insertWidget(0,ui->pushButton3);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerB){

        ui->VL2->insertWidget(0,ui->pushButton3);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerC){

        ui->VL3->insertWidget(0,ui->pushButton3);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    Activate1();  Activate2();  Activate3();  Activate4();

    ButtonSize();

    Counter++;
    CountMove();

    CheckWin();

    ui->label_Hint->setText("Choose     Tower");
}

//Button 4 Click Function
void MainWindow::on_pushButton4_clicked()
{
    //Check Destination Tower & Move Button To The Tower
    if(CheckTowerA){

        ui->VL1->insertWidget(0,ui->pushButton4);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerB){

        ui->VL2->insertWidget(0,ui->pushButton4);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    else if(CheckTowerC){

        ui->VL3->insertWidget(0,ui->pushButton4);

        CheckTowerA = CheckTowerB = CheckTowerC = false;
    }
    Activate1();  Activate2();  Activate3();  Activate4();

    ButtonSize();

    Counter++;
    CountMove();

    CheckWin();

    ui->label_Hint->setText("Choose     Tower");
}

//Tower A Destitantion Function
void MainWindow::on_pushButtonA_clicked()
{
    CheckTowerA = true;
    CheckTowerB = CheckTowerC = false;

    Activate1();
    Activate2();
    Activate3();
    Activate4();

    ui->label_Hint->setText("Choose     Number");

    Starter();
}

//Tower B Destitantion Function
void MainWindow::on_pushButtonB_clicked()
{
    CheckTowerB = true;
    CheckTowerA = CheckTowerC = false;

    Activate1();
    Activate2();
    Activate3();
    Activate4();

    ui->label_Hint->setText("Choose     Number");

    Starter();
}

//Tower C Destitantion Function
void MainWindow::on_pushButtonC_clicked()
{
    CheckTowerC = true;
    CheckTowerA = CheckTowerB = false;

    Activate1();
    Activate2();
    Activate3();
    Activate4();

    ui->label_Hint->setText("Choose     Number");

    Starter();
}


//Function To Fix The Size Of Buttons
void MainWindow::ButtonSize(){

    ui->pushButton1->setFixedSize(90,50);
    ui->VL1->setAlignment(ui->pushButton1,Qt::AlignHCenter);
    ui->VL2->setAlignment(ui->pushButton1,Qt::AlignHCenter);
    ui->VL3->setAlignment(ui->pushButton1,Qt::AlignHCenter);

    ui->pushButton2->setFixedSize(120,50);
    ui->VL1->setAlignment(ui->pushButton2,Qt::AlignHCenter);
    ui->VL2->setAlignment(ui->pushButton2,Qt::AlignHCenter);
    ui->VL3->setAlignment(ui->pushButton2,Qt::AlignHCenter);

    ui->pushButton3->setFixedSize(150,50);
    ui->VL1->setAlignment(ui->pushButton3,Qt::AlignHCenter);
    ui->VL2->setAlignment(ui->pushButton3,Qt::AlignHCenter);
    ui->VL3->setAlignment(ui->pushButton3,Qt::AlignHCenter);

    ui->pushButton4->setFixedSize(180,50);
    ui->VL1->setAlignment(ui->pushButton4,Qt::AlignHCenter);
    ui->VL2->setAlignment(ui->pushButton4,Qt::AlignHCenter);
    ui->VL3->setAlignment(ui->pushButton4,Qt::AlignHCenter);
}

//Guide Button Function
void MainWindow::on_actionGuide_triggered()
{
    Timer->stop();
    StopStart = true;

    QMessageBox::information(this,"GAME TUTORIAL","In This Game You Must Move All Buttons In Tower A , In The Same Order To The Tower C \n"
                                                    "There Are Some Rules For Game : \n"
                                                    " -You Can't Take Out Button Under The Other \n"
                                                    " -You Can't Move Bigger Button On Top Of Smaller One \n"
                                                    " -You Have One Minute To Complete The Game & If You Can't Make It Under A Minute You Lose \n"
                                                    "For Playing The Gmae Fist You Must Select Destination Tower & If There Is Any Selectable Button \n"
                                                    "From 1 to 4 They Become Active & You Can Select Them & If No Button Is Selectable You Must Choose \n"
                                                    "Another Tower");

}

//Exit Button Function
void MainWindow::on_actionExit_triggered()
{
    Timer->stop();
    StopStart = true;

    QMessageBox MsgBox;
    MsgBox.setWindowTitle("Exit");
    MsgBox.setText("Are You Sure ?");
    MsgBox.setIcon(QMessageBox::Warning);
    MsgBox.setStandardButtons(QMessageBox::Yes);
    MsgBox.addButton(QMessageBox::No);
    MsgBox.setDefaultButton(QMessageBox::No);
    if(MsgBox.exec() == QMessageBox::Yes){

        QCoreApplication::quit();
    }
}

//Timer Button Function To Control Timer
void MainWindow::on_pushButton_Timer_clicked()
{
    if(!StopStart){

        Timer->stop();
        StopStart = true;
        ui->pushButton_Timer->setText("Start");
        return;
    }
    else if(StopStart){

        Timer->start(1000);
        StopStart = false;
        ui->pushButton_Timer->setText("Stop");
        return;
    }
}

//Timer Starter Function To Start Each Time User Is Playing
void MainWindow::Starter(){

    if(StopStart){

        Timer->start(1000);
        StopStart = false;
        ui->pushButton_Timer->setText("Stop");
        return;
    }
}

void MainWindow::on_actionRestart_triggered()
{
    ResetGame();

}

//Restart Function
void MainWindow::ResetGame(){

    Counter = 0;
    ui->label_Count->setText("0     Moves");

    ui->VL1->insertWidget(0,ui->pushButton1);
    ui->VL1->insertWidget(1,ui->pushButton2);
    ui->VL1->insertWidget(2,ui->pushButton3);
    ui->VL1->insertWidget(3,ui->pushButton4);
    activation1 = activation2 = activation3 = activation4 = false;
    ui->pushButton1->setEnabled(activation1);
    ui->pushButton2->setEnabled(activation2);
    ui->pushButton3->setEnabled(activation3);
    ui->pushButton4->setEnabled(activation4);

    ButtonSize();

    Time.setHMS(0,1,30);
    Timer->stop();
    StopStart = true;
    UpdateTimer();
    ui->label_Timer->setText("01 : 30");
    ui->pushButton_Timer->setText("Start");
}

//Count User Moves Function
void MainWindow::CountMove(){

    QString Count = QString::number(Counter);
    ui->label_Count->setText(Count + "     Moves");
}
