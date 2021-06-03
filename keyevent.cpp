#include "keyevent.h"
#include <QApplication>
#include <QKeyEvent>
#include "KeyEvent.h"
#include"mainwindow.h"

KeyEvent::KeyEvent(QWidget *parent){

}

void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {
        qDebug()<<"test";
    }
}
