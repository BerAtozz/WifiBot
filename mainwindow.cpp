#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <myrobot.h>
#include <Windows.h>
#include <QtGui>
#include <QApplication>
#include <QKeyEvent>
#include "keypress.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GroBot = new MyRobot();
    camera = new Camera();

    ui->lcdSpeed->setPalette(Qt::darkRed);
    connect( ui->velocity, SIGNAL(valueChanged(int)), ui->lcdSpeed, SLOT(display(int)) );
    connect(this->GroBot, SIGNAL(updateUI(QByteArray)), this, SLOT(reloadDisplay(QByteArray)));

    KeyPress *keyPress = new KeyPress();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_boutonConnexion_clicked()
{
    camera->deleteVideo(ui);

    bool status;
    status = GroBot->doConnect();
    ui->forwardButon->setEnabled(status);
    ui->backwardButton->setEnabled(status);
    ui->leftButton->setEnabled(status);
    ui->rightButton->setEnabled(status);
    ui->DownCam->setEnabled(status);
    ui->UpCam->setEnabled(status);
    ui->leftCam->setEnabled(status);
    ui->rightCam->setEnabled(status);

    camera->displayVideo(ui);
}

void MainWindow::on_velocity_valueChanged(int value)
{
    velocity = ui->velocity->value();
}

void MainWindow::on_forwardButon_released()
{
    GroBot->Stop();
}

void MainWindow::on_forwardButon_pressed()
{
    GroBot->Forward(velocity);
}

void MainWindow::on_backwardButton_pressed()
{
    GroBot->Backward(velocity);
}

void MainWindow::on_backwardButton_released()
{
    GroBot->Stop();
}

void MainWindow::on_leftButton_pressed()
{
    GroBot->Left(velocity);
}

void MainWindow::on_leftButton_released()
{
   GroBot->Stop();
}

void MainWindow::on_rightButton_pressed()
{
    GroBot->Right(velocity);
}

void MainWindow::on_rightButton_released()
{
    GroBot->Stop();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        GroBot->Forward(velocity);
    }
    if(event->key() == Qt::Key_Down)
    {
        GroBot->Backward(velocity);
    }
    if(event->key() == Qt::Key_Left)
    {
        GroBot->Left(velocity);
    }
    if(event->key() == Qt::Key_Right)
    {
        GroBot->Right(velocity);
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_Down)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_Left)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_Right)
    {
        GroBot->Stop();
    }
}


void MainWindow::on_leftCam_pressed()
{
    camera->moveLeft();
}

void MainWindow::on_rightCam_pressed()
{
    camera->moveRight();
}

void MainWindow::on_UpCam_pressed()
{
    camera->moveUp();
}

void MainWindow::on_DownCam_pressed()
{
    camera->moveDown();
}

void MainWindow::reloadDisplay(QByteArray retour){
    changeBattery(retour[2]);
}

void MainWindow::changeBattery(unsigned char bat){
    int bat_int = (int)bat;
    bat_int-=3;
    if(bat_int > 124){
        bat_int=124;
    }
    else if(bat_int < 0){
        bat_int = 0;
    }
    bat_int=bat_int*100/124;
    ui->batteryBar->setValue(bat_int);
}




