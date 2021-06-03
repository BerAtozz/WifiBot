#include "camera.h"
#include <QWebEngineView>


Camera::Camera()
{

}

void Camera::displayVideo(Ui::MainWindow *ui){
    view = new QWebEngineView();
    ui->video->addWidget(view);
    view->load(QUrl("http://192.168.1.11:8080/?action=stream"));
    view->show();
}

void Camera::moveLeft()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=255"));
}

void Camera::moveRight()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-255"));
}

void Camera::moveUp()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-255"));

}

void Camera::moveDown()
{
    url = new QWebEngineView();
    url->load(QUrl("http://192.168.1.11:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=255"));
}
