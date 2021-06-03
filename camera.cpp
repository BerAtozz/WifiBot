#include "camera.h"
#include <QWebEngineView>

Camera::Camera()
{

}

void Camera::displayVideo(Ui::MainWindow *ui){
    QWebEngineView *view = new QWebEngineView();
    ui->video->addWidget(view);
    view->load(QUrl("http://192.168.1.11:8080/?action=stream"));
    view->show();
}
