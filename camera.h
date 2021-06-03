#ifndef CAMERA_H
#define CAMERA_H
#include "ui_mainwindow.h"
#include <QWebEngineView>


class Camera
{
public:
    Camera();
    void displayVideo(Ui::MainWindow *ui);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
private:
    QWebEngineView *view;
    QWebEngineView *url;
};

#endif // CAMERA_H
