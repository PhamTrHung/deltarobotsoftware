#include "connectionsettings.h"
#include "ui_connectionsettings.h"

ConnectionSettings::ConnectionSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);

    setPortParameters();
    fillPortInfors();

    updateSettings();
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;
}

void ConnectionSettings::on_btnApply_clicked()
{
    isSettings = true;
    updateSettings();
    hide();
}

void ConnectionSettings::updateSettings()
{
    m_currentSettings.name = ui->cmbCom->currentText();

    QString baudrateData = ui->cmbBaudrate->currentText();
    m_currentSettings.baudRate = baudrateData.toInt();
    m_currentSettings.stringBaudRate = baudrateData;

    const auto dataBitsData = ui->cmbDataBits->currentData();
    m_currentSettings.dataBits = dataBitsData.value<QSerialPort::DataBits>();
    m_currentSettings.stringDataBits = ui->cmbDataBits->currentText();

    const auto parityData =  ui->cmbParity->currentData();
    m_currentSettings.parity = parityData.value<QSerialPort::Parity>();
    m_currentSettings.stringParity = ui->cmbParity->currentText();

    const auto stopBitsData = ui->cmbStopBits->currentData();
    m_currentSettings.stopBits = stopBitsData.value<QSerialPort::StopBits>();
    m_currentSettings.stringStopBits = ui->cmbStopBits->currentText();
}

void ConnectionSettings::fillPortInfors()
{
    ui->cmbCom->clear();

    foreach (auto &infor, QSerialPortInfo::availablePorts()) {
        ui->cmbCom->addItem(infor.portName());
    }
}

void ConnectionSettings::setPortParameters()
{
    ui->cmbBaudrate->setItemData(0, QSerialPort::Baud9600);
    ui->cmbBaudrate->setItemData(1, QSerialPort::Baud38400);
    ui->cmbBaudrate->setItemData(2, QSerialPort::Baud115200);

    ui->cmbDataBits->setItemData(0, QSerialPort::Data8);
    ui->cmbDataBits->setItemData(1, QSerialPort::Data7);

    ui->cmbStopBits->setItemData(0, QSerialPort::OneStop);
    ui->cmbStopBits->setItemData(1, QSerialPort::TwoStop);
}


ConnectionSettings::Settings ConnectionSettings::settings() const
{
    return m_currentSettings;
}


