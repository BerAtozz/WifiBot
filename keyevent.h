#ifndef KEYEVENT_H
#define KEYEVENT_H
#include <QWidget>
#include <QtGui>


class KeyEvent
{
public:
    KeyEvent(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // KEYEVENT_H
