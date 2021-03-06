
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <myrobot.h>
#include <camera.h>
#include <QApplication>
#include <QKeyEvent>
#include <keyevent.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficherMessage();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void changeBattery(unsigned char bat);
    void changeIR(unsigned char IRfl, unsigned char IRbr, unsigned char IRfr, unsigned char IRbl);
    void displayRealSpeed(int leftSpeed, int rightSpeed);

private slots:
    void on_boutonConnexion_clicked();
    void on_deconnexion_clicked();

    void on_velocity_valueChanged(int value);

    void on_forwardButon_released();
    void on_forwardButon_pressed();

    void on_backwardButton_pressed();
    void on_backwardButton_released();

    void on_leftButton_pressed();
    void on_rightButton_pressed();

    void on_leftButton_released();
    void on_rightButton_released();

    void on_FLeft_pressed();
    void on_FLeft_released();

    void on_FRight_pressed();
    void on_FRight_released();

    void on_BRight_pressed();
    void on_BRight_released();

    void on_BLeft_pressed();
    void on_BLeft_released();

    void on_leftCam_pressed();
    void on_rightCam_pressed();
    void on_UpCam_pressed();
    void on_DownCam_pressed();

    void reloadDisplay(QByteArray retour);



private:
    Ui::MainWindow *ui;
    int velocity;
    MyRobot *GroBot;
    Camera *camera;


};
#endif // MAINWINDOW_H
