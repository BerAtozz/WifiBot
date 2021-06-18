#include "camera.h"
#include <QWebEngineView>


Camera::Camera()
{
    view = new QWebEngineView();


}

void Camera::initCameraView(Ui::MainWindow *ui){
    ui->video->addWidget(view);
    view->load(QUrl("http://localhost/"));
    view->show();
}

void Camera::displayVideo(Ui::MainWindow *ui){    
    ui->video->addWidget(view);
    view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    view->show();
}

void Camera::deleteVideo(Ui::MainWindow *ui){
    ui->video->removeWidget(view);
}

void Camera::moveLeft()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=255"));
}

void Camera::moveRight()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-255"));
}

void Camera::moveUp()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-255"));

}

void Camera::moveDown()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=255"));
}
