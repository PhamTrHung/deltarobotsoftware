#include "connectionmanager.h"
#include "QMessageBox"
#include "QDebug"

ConnectionManager::ConnectionManager() {
    init();
}

ConnectionManager::~ConnectionManager()
{
    if(m_serial != nullptr) delete m_serial;
    if(m_settings != nullptr) delete m_settings;
}

void ConnectionManager::init()
{
    m_settings = new ConnectionSettings();
    m_serial = new QSerialPort();
}

void ConnectionManager::processReceiveData()
{
    if(receiveLine.mid(0,2) == "Ok" || (receiveLine.indexOf('k') > -1 && receiveLine.indexOf('O') > -1)
                                    || receiveLine.mid(0, 7) == "Unknown"){

        emit deltaRespondGcodeDone();
    }
}


void ConnectionManager::openConnectionSettingUi()
{
    m_settings->show();
}

void ConnectionManager::connectToRobot()
{
    const ConnectionSettings::Settings p = m_settings->settings();

    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setStopBits(p.stopBits);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if(m_serial->open(QIODevice::ReadWrite)){
        portName = p.name;
        isConnecToDeltaRobot = true;

        connect(m_serial, SIGNAL(readyRead()), this, SLOT(readData()));
    }else{
        isConnecToDeltaRobot = false;
    }
}

void ConnectionManager::disconnectToRobot()
{
    if(m_serial->isOpen()) m_serial->close();
    isConnecToDeltaRobot = false;
}

bool ConnectionManager::isDeltaRobotConnect()
{
    return isConnecToDeltaRobot;
}

QString ConnectionManager::getPortName()
{
    return portName;
}

void ConnectionManager::sendData(QString msg)
{
    msg += "\n";

    if(m_serial->isOpen()) m_serial->write(msg.toStdString().c_str(), msg.size());
    return;
}

void ConnectionManager::updatePortInfor()
{
    m_settings->fillPortInfors();
}

void ConnectionManager::readData()
{
    //Trong trường hợp dùng thêm tcp truyền nhận data thì mới cần dùng con trỏ p
    //QSerialPort* p = qobject_cast<QSerialPort*>(sender());

    while(m_serial->canReadLine()){
        receiveLine = m_serial->readLine();
        //qDebug() << receiveLine;

        processReceiveData();
    }
}


