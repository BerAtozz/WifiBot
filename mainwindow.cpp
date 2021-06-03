#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <myrobot.h>
#include <Windows.h>
#include <QtGui>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GroBot = new MyRobot();
    camera = new Camera();


    ui->lcdSpeed->setPalette(Qt::red);
    connect( ui->velocity, SIGNAL(valueChanged(int)), ui->lcdSpeed, SLOT(display(int)) );
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_boutonConnexion_clicked()
{
    bool status;
    status = GroBot->doConnect();
    ui->forwardButon->setEnabled(status);
    ui->backwardButton->setEnabled(status);
    ui->leftButton->setEnabled(status);
    ui->rightButton->setEnabled(status);

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




