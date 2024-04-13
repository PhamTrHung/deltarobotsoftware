#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class ConnectionSettings;
}

class ConnectionSettings : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
    };

    Settings settings() const;
    bool isSettings = false;

public:
    explicit ConnectionSettings(QWidget *parent = nullptr);
    ~ConnectionSettings();

    void fillPortInfors();

private slots:
    void on_btnApply_clicked();

private:
    Ui::ConnectionSettings *ui;
    Settings m_currentSettings;
    void updateSettings();

    void setPortParameters();
};

#endif // CONNECTIONSETTINGS_H
