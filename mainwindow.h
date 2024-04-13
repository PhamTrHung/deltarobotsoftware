#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "connectionsettings.h"
#include "connectionmanager.h"
#include "deltavisualizer.h"
#include "imageprocessor.h"
#include "objectvariabletable.h"
#include "gcodewindow.h"
#include "gcodeprogrammanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void initVariables();
    void initEvents();

    DeltaVisualizer* delta2DVisualizer;
    ImageProcessor* deltaImageProcessor;
    ObjectVariableTable* trackingObjectTable;
    GCodeWindow* gcodeView;
    GcodeProgramManager* deltaGcodeManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void connectionSettings();
    void triggerConnect();
    void goToHome();

    void updateXYZLabelFrom2dControl(float, float, float);
    void updateZLableValue(int);
    void updateValueWhenClickGo();
    void updateDeltaPositionFromGUI();

    void turnOnConveyor();
    void turnOffConveyor();
    void setSpeedForConveyor();

    void updateInfor_LoadCamera();
    void changeModeDisplay();

    void executeProgram();
    void saveProgram();
    void loadProgram();

    void activateVacuum();

    void changeCalibTool();

private:
    Ui::MainWindow *ui;

    ConnectionManager* m_connection = nullptr;
    QLabel *m_status = nullptr;
    void showStatusMessage(const QString &message);
    bool isConnected = false;



};
#endif // MAINWINDOW_H
