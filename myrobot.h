
#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    bool doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    short crcSoft(unsigned char Adresse_tab , unsigned char Taille_max);
    quint16 crc16(QByteArray byteArray, int pos);

    void Forward(int velocity);
    void Backward(int velocity);    
    void Left(int velocity);
    void Right(int velocity);

    void FLeft(int velocity);
    void FRight(int velocity);
    void BLeft(int velocity);
    void BRight(int velocity);

    void Stop();

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    int clockTimer;
};

#endif // MYROBOT_H
