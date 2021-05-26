#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <myrobot.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficherMessage();
    MyRobot *GroBot;
private slots:
    void on_boutonConnexion_clicked();

    void on_forwardButon_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
