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
    camera->initCameraView(ui);

    ui->lcdSpeed->setPalette(Qt::darkRed);

    connect( ui->velocity, SIGNAL(valueChanged(int)), ui->lcdSpeed, SLOT(display(int)) );
    connect(this->GroBot, SIGNAL(updateUI(QByteArray)), this, SLOT(reloadDisplay(QByteArray)));

    //KeyPress *keyPress = new KeyPress();
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
 * Méthode apellée à la l'appui sur le bouton connexion
 * Affiche la caméra et rend les boutons clickable
 */
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

    ui->BLeft->setEnabled(status);
    ui->BRight->setEnabled(status);
    ui->FLeft->setEnabled(status);
    ui->FRight->setEnabled(status);
    ui->boutonConnexion->setEnabled(false);

    camera->displayVideo(ui);
}

/*
 * Méthode apellée lors de l'appui sur le bouton Déconnexion
 * Supprime la caméra et rend et rend les boutons non clickable
 */
void MainWindow::on_deconnexion_clicked(){
    camera->deleteVideo(ui);
    camera->initCameraView(ui);

    bool status;
    GroBot->disConnect();
    status = false;

    ui->forwardButon->setEnabled(status);
    ui->backwardButton->setEnabled(status);
    ui->leftButton->setEnabled(status);
    ui->rightButton->setEnabled(status);

    ui->DownCam->setEnabled(status);
    ui->UpCam->setEnabled(status);
    ui->leftCam->setEnabled(status);
    ui->rightCam->setEnabled(status);

    ui->BLeft->setEnabled(status);
    ui->BRight->setEnabled(status);
    ui->FLeft->setEnabled(status);
    ui->FRight->setEnabled(status);
    ui->boutonConnexion->setEnabled(true);

}

/*
 * Récupère et stocke la valeur de la vitesse max
 */
void MainWindow::on_velocity_valueChanged(int value)
{
    velocity = ui->velocity->value();
}

/*
 * Méthodes liées au déplacement du robot
 */
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


void MainWindow::on_FLeft_pressed(){
    GroBot->FLeft(velocity);
}
void MainWindow::on_FLeft_released(){
    GroBot->Stop();
}


void MainWindow::on_FRight_pressed(){
    GroBot->FRight(velocity);
}
void MainWindow::on_FRight_released(){
    GroBot->Stop();
}


void MainWindow::on_BLeft_pressed(){
    GroBot->BLeft(velocity);
}
void MainWindow::on_BLeft_released(){
    GroBot->Stop();
}


void MainWindow::on_BRight_pressed(){
    GroBot->BRight(velocity);
}
void MainWindow::on_BRight_released(){
    GroBot->Stop();
}


/*
 * Méthodes qui relève les appuis clavier pour le déplacement du robot
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z)
    {
        GroBot->Forward(velocity);
    }
    if(event->key() == Qt::Key_S)
    {
        GroBot->Backward(velocity);
    }
    if(event->key() == Qt::Key_Q)
    {
        GroBot->Left(velocity);
    }
    if(event->key() == Qt::Key_D)
    {
        GroBot->Right(velocity);
    }
    if(event->key() == Qt::Key_A)
    {
        GroBot->FLeft(velocity);
    }
    if(event->key() == Qt::Key_E)
    {
        GroBot->FRight(velocity);
    }
    if(event->key() == Qt::Key_W)
    {
        GroBot->BLeft(velocity);
    }
    if(event->key() == Qt::Key_C)
    {
        GroBot->BRight(velocity);
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Z)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_S)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_Q)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_D)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_A)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_E)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_W)
    {
        GroBot->Stop();
    }
    if(event->key() == Qt::Key_C)
    {
        GroBot->Stop();
    }
}

/*
 * Méthodes liées au déplcement de la caméra
 */
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

/*
 * Méthode qui récupère les données de retour
 */
void MainWindow::reloadDisplay(QByteArray retour){
    changeBattery(retour[2]);    
    changeIR(retour[3],retour[4],retour[11],retour[12]);

    int speedLeft = (int)(retour[1] << 8 + retour[0]);
    int speedRight = (int)(retour[10] << 8 + retour[9]);

    displayRealSpeed(speedLeft, speedRight);
}

/*
 * Affiche le niveau de batterie sur l'UI
 */
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

/*
 * Affiche les niveau des capteurs IR sur l'UI
 */
void MainWindow::changeIR(unsigned char IRfl, unsigned char IRbr,unsigned char IRfr, unsigned char IRbl){
    ui->irFrontLeft->setValue((int)IRfl);
    ui->irBackRight->setValue((int)IRbr);
    ui->irFrontRight->setValue((int) IRfr);
    ui->irBackLeft->setValue((int)IRbl);
}

/*
 * Affiche les vitesses gauche et droite
 */
void MainWindow::displayRealSpeed(int leftSpeed, int rightSpeed){
    ui->speedLeft->setValue(leftSpeed);
    ui->speedRight->setValue(rightSpeed);
}




