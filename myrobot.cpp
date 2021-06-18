#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}


bool MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return false;
    }
    TimerEnvoi->start(75);
    return true;

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.

}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    //qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

quint16 MyRobot::crc16(QByteArray byteArray, int pos){
    byteArray.data();
    unsigned char *data = (unsigned char*)byteArray.constData();
    quint16 crc=0xFFFF;
    quint16 Polynome = 0xA001;
    quint16 Parity=0;
    for(;pos < byteArray.length()-2; pos++){
        crc ^= *(data+pos);
        for(unsigned int CptBit = 0; CptBit <=7; CptBit++){
            Parity = crc;
            crc >>= 1;
            if(Parity%2 == true){
                crc ^= Polynome;
            }
        }
    }
    return crc;
}

void MyRobot::Forward(int velocity){

        while(Mutex.tryLock());

        DataToSend[2]=(unsigned char)velocity;
        DataToSend[3]=0;
        DataToSend[4]=(unsigned char)velocity;
        DataToSend[5]=0;
        DataToSend[6]=0x50;

        quint16 crcRes = crc16(DataToSend,1);

        DataToSend[7]= (unsigned char)crcRes;
        DataToSend[8]= (unsigned char)(crcRes>>8);
        Mutex.unlock();

}

void MyRobot::Backward(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(unsigned char)velocity;
    DataToSend[3]=0;
    DataToSend[4]=(unsigned char)velocity;
    DataToSend[5]=0;
    DataToSend[6]=0;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}

void MyRobot::Stop(){
    Forward(40);
}

void MyRobot::FLeft(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(((unsigned char)velocity)/2);
    DataToSend[3]=0;
    DataToSend[4]=(unsigned char)velocity;
    DataToSend[5]=0;
    DataToSend[6]=0x50;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}

void MyRobot::BLeft(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(((unsigned char)velocity)/2);
    DataToSend[3]=0;
    DataToSend[4]=(unsigned char)velocity;
    DataToSend[5]=0;
    DataToSend[6]=0;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}

void MyRobot::Left(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(0);
    DataToSend[3]=0;
    DataToSend[4]=(unsigned char)velocity;
    DataToSend[5]=0;
    DataToSend[6]=0x50;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}

void MyRobot::FRight(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(unsigned char)velocity;
    DataToSend[3]=0;
    DataToSend[4]=(((unsigned char)velocity)/2);
    DataToSend[5]=0;
    DataToSend[6]=0x50;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}

void MyRobot::BRight(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(unsigned char)velocity;
    DataToSend[3]=0;
    DataToSend[4]=(((unsigned char)velocity)/2);
    DataToSend[5]=0;
    DataToSend[6]=0;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}

void MyRobot::Right(int velocity){
    while(Mutex.tryLock());

    DataToSend[2]=(unsigned char)velocity;
    DataToSend[3]=0;
    DataToSend[4]=(0);
    DataToSend[5]=0;
    DataToSend[6]=0x50;

    quint16 crcRes = crc16(DataToSend,1);

    DataToSend[7]= (unsigned char)crcRes;
    DataToSend[8]= (unsigned char)(crcRes>>8);
    Mutex.unlock();
}
