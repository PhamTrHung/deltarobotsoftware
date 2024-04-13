#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QSerialPort>
#include <QSerialPortInfo>

#include "connectionsettings.h"


class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    ConnectionManager();
    ~ConnectionManager();

    void openConnectionSettingUi();
    void connectToRobot();
    void disconnectToRobot();
    bool isDeltaRobotConnect();
    QString getPortName();

    void sendData(QString msg);

    void updatePortInfor();

public slots:
    void readData();

signals:
    void deltaRespondGcodeDone();

private:
    void init();
    void processReceiveData();


    ConnectionSettings *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
    bool isConnecToDeltaRobot = false;
    QString portName;

    QString receiveLine;

};

#endif // CONNECTIONMANAGER_H
