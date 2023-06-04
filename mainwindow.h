#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPushButton"
#include "QTimer"
#include "QTime"
#include "QLabel"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Menu Buttons
    QPushButton *Start;
    QPushButton *Help;
    QPushButton *Quit;

    //Destination Tower Checkers
    bool CheckTowerA = false;
    bool CheckTowerB = false;
    bool CheckTowerC = false;

    //Button 1 to 4 Activator Functions
    void Activate1();
    void Activate2();
    void Activate3();
    void Activate4();
    bool activation1 = false;
    bool activation2 = false;
    bool activation3 = false;
    bool activation4 = false;

    //Bigger Button On Smaller Button Function
    void CanClick1();
    void CanClick2();
    void CanClick3();
    bool ClickA1 = true;
    bool ClickB1 = true;
    bool ClickC1 = true;
    bool ClickA2 = true;
    bool ClickB2 = true;
    bool ClickC2 = true;
    bool ClickA3 = true;
    bool ClickB3 = true;
    bool ClickC3 = true;

    //Win Or Loose Functions
    void CheckWin();
    void CheckLoose();

    void ButtonSize();  // Button Fixed Size Function

    //Start Timer
    void Starter();
    bool StopStart = true;

    qint8 Counter = 0;  //User Moves Counter

public slots:

    //Menu Button Functions
    void StartButton();
    void HelpButton();
    void QuitButton();

    void UpdateTimer();  //Timer Function

    void ResetGame();  //Restart Whole Game

    void CountMove();  //Count Moves

private slots:

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButtonB_clicked();

    void on_pushButtonC_clicked();

    void on_pushButtonA_clicked();

    void on_actionGuide_triggered();

    void on_actionExit_triggered();

    void on_pushButton_Timer_clicked();

    void on_actionRestart_triggered();

private:
    Ui::MainWindow *ui;

    //Timer
    QTime Time;
    QTimer *Timer;
};
#endif // MAINWINDOW_H
