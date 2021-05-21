#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <myrobot.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_boutonConnexion_clicked()
{

    MyRobot().doConnect();
}

void MainWindow::on_forwardButon_clicked()
{
    MyRobot().Forward();
}

