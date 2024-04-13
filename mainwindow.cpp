#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initVariables();
    initEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_connection != nullptr) delete m_connection;
}

void MainWindow::initVariables()
{
    m_connection = new ConnectionManager();
    m_status = new QLabel(this);

    ui->statusbar->addWidget(m_status);
    ui->btnConnect->setEnabled(false);
    ui->btnSettingConnect->setEnabled(true);

    //2D visualizer
    delta2DVisualizer = new DeltaVisualizer(ui->t2D);
    delta2DVisualizer->setObjectName(QStringLiteral("wg2d"));
    delta2DVisualizer->setGeometry(QRect(50,30,370,355));
    delta2DVisualizer->setDivisionCombobox(ui->cmbDivision);
    delta2DVisualizer->changeXY(0, 0);

    //Image processor
    deltaImageProcessor = new ImageProcessor(this);
    deltaImageProcessor->setImageScreen(ui->lblCam);
    deltaImageProcessor->setObjectInforLabelWidget(ui->lbTrackingObjectNumber, ui->lbVisibleObjectNumber);
    deltaImageProcessor->setMeasureParameterPointer(ui->leXCoordinate, ui->leYCoordinate, ui->leRealDistance);

    //Object table
    trackingObjectTable = new ObjectVariableTable(this);

    //Gcode
    gcodeView = new GCodeWindow(this);
    deltaGcodeManager = new GcodeProgramManager(gcodeView->teGcodeWidget, ui->btnStartProgram, m_connection);

}

void MainWindow::initEvents()
{
    //control robot
    connect(ui->btnSettingConnect, SIGNAL(clicked(bool)), this, SLOT(connectionSettings()));
    connect(ui->btnConnect, SIGNAL(clicked(bool)), this, SLOT(triggerConnect()));
    connect(ui->btnHoming, SIGNAL(clicked(bool)), this, SLOT(goToHome()));

    connect(ui->btnForward, SIGNAL(clicked(bool)), delta2DVisualizer, SLOT(moveForward()));
    connect(ui->btnBackward, SIGNAL(clicked(bool)), delta2DVisualizer, SLOT(moveBackward()));
    connect(ui->btnLeft, SIGNAL(clicked(bool)), delta2DVisualizer, SLOT(moveLeft()));
    connect(ui->btnRight, SIGNAL(clicked(bool)), delta2DVisualizer, SLOT(moveRight()));
    connect(ui->btnUp, SIGNAL(clicked(bool)), delta2DVisualizer, SLOT(moveUp()));
    connect(ui->btnDown, SIGNAL(clicked(bool)), delta2DVisualizer, SLOT(moveDown()));

    connect(delta2DVisualizer, SIGNAL(moved(float,float,float)), this, SLOT(updateXYZLabelFrom2dControl(float,float,float)));
    connect(delta2DVisualizer, SIGNAL(finishMoving()), this, SLOT(updateDeltaPositionFromGUI()));

    connect(ui->sldZAdjustion, SIGNAL(sliderReleased()), this, SLOT(updateDeltaPositionFromGUI()));
    connect(ui->sldZAdjustion, SIGNAL(valueChanged(int)), this, SLOT(updateZLableValue(int)));
    connect(ui->btnGo, SIGNAL(clicked(bool)), this, SLOT(updateValueWhenClickGo()));

    //control conveyor
    connect(ui->btnTurnOnConveyor, SIGNAL(clicked(bool)), this, SLOT(turnOnConveyor()));
    connect(ui->btnTurnOffConveyor, SIGNAL(clicked(bool)), this, SLOT(turnOffConveyor()));
    connect(ui->btnSetSpeedConveyor, SIGNAL(clicked(bool)), this, SLOT(setSpeedForConveyor()));

    //Image processor, camera
    connect(ui->btnLoadCam, SIGNAL(clicked(bool)), this, SLOT(updateInfor_LoadCamera()));
    connect(ui->btnCaptureImage, SIGNAL(clicked(bool)), deltaImageProcessor, SLOT(saveImage()));
    //connect(ui->btnFilter, SIGNAL(clicked(bool)), deltaImageProcessor, SLOT(openParameterPanel()));
    connect(ui->cmbModeDisplay, SIGNAL(currentTextChanged(QString)), this, SLOT(changeModeDisplay()));
    connect(ui->btnClearAllObject, SIGNAL(clicked(bool)), deltaImageProcessor->obManager, SLOT(removeAllDetectObjects()));

    //Vacuum
    connect(ui->btnVacuum, SIGNAL(clicked()), this, SLOT(activateVacuum()));

    //Object tracking
    connect(deltaImageProcessor, SIGNAL(objectPositionChanged(std::vector<cv::RotatedRect>)), trackingObjectTable, SLOT(updateTable(std::vector<cv::RotatedRect>)));
    connect(ui->btnShowObjectTrackingTable, SIGNAL(clicked(bool)), trackingObjectTable, SLOT(displayDialog()));


    //Gcode
    connect(ui->btnGCodeView, SIGNAL(clicked(bool)), gcodeView, SLOT(show()));
    connect(gcodeView, SIGNAL(addNewGcodeLine(QString)), deltaGcodeManager, SLOT(addGcodeLine(QString)));
    connect(ui->btnStartProgram, SIGNAL(clicked(bool)), this, SLOT(executeProgram()));
    connect(gcodeView, SIGNAL(saveGcodeInEditorToFile()), this, SLOT(saveProgram()));
    connect(gcodeView, SIGNAL(loadProgram()), this, SLOT(loadProgram()));

    //Camera Widget
    connect(ui->btnLine, SIGNAL(clicked(bool)), this, SLOT(changeCalibTool()));
    connect(ui->btnRectangle, SIGNAL(clicked(bool)), this, SLOT(changeCalibTool()));
    connect(ui->btnPoint, SIGNAL(clicked(bool)), this, SLOT(changeCalibTool()));

    //Calib camera
    connect(ui->lblCam, SIGNAL(finishMeasureSpace(int)), deltaImageProcessor, SLOT(getDistance(int)));
    connect(ui->lblCam, SIGNAL(finishSelectCalibLine(QPoint,QPoint)), deltaImageProcessor, SLOT(getCalibLine(QPoint,QPoint)));
    connect(ui->lblCam, SIGNAL(finishSelectCalibPoint(int,int)), deltaImageProcessor, SLOT(getCalibPoint(int,int)));
    connect(ui->lblCam, SIGNAL(finishSelectProcessArea(QRect)), deltaImageProcessor, SLOT(getProcessArea(QRect)));
}

void MainWindow::triggerConnect()
{
    if(!isConnected){
        m_connection->connectToRobot();
        if(m_connection->isDeltaRobotConnect()){
            ui->btnSettingConnect->setEnabled(false);
            ui->btnConnect->setText("Disconnect");
            showStatusMessage(tr("Connected to %1 success").arg(m_connection->getPortName()));
            isConnected = true;
        }else{
            QMessageBox::critical(this, "Error", "Could not connect to Delta Robot");
            showStatusMessage(tr("Open Error!!!"));
        }
    }else{
        m_connection->disconnectToRobot();
        ui->btnConnect->setText(tr("Connect"));
        showStatusMessage(tr("Disconnect to Delta Robot"));
        ui->btnSettingConnect->setEnabled(true);
        isConnected = false;
    }

}


void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

void MainWindow::connectionSettings()
{
    m_connection->updatePortInfor();
    m_connection->openConnectionSettingUi();
    ui->btnConnect->setEnabled(true);
}

void MainWindow::goToHome()
{
    if(m_connection->isDeltaRobotConnect()){
        m_connection->sendData("G28");

        ui->lbX->setText(QString::number(delta2DVisualizer->XHome));
        ui->lbY->setText(QString::number(delta2DVisualizer->YHome));
        ui->lbZ->setText(QString::number(delta2DVisualizer->ZHome));

        ui->sldZAdjustion->setValue(0);

        delta2DVisualizer->changeXY(0, 0);
    }
}

void MainWindow::updateXYZLabelFrom2dControl(float x, float y, float z)
{
    ui->lbX->setText(QString::number(x));
    ui->lbY->setText(QString::number(y));
    ui->lbZ->setText(QString::number(z));

    ui->sldZAdjustion->setValue(delta2DVisualizer->ZHome - z);
}

void MainWindow::updateZLableValue(int z)
{
    ui->lbZ->setText(QString::number(delta2DVisualizer->ZHome - z));
    delta2DVisualizer->Z = delta2DVisualizer->ZHome - z;
}

void MainWindow::updateValueWhenClickGo()
{
    delta2DVisualizer->X = ui->leXValue->text().toFloat();
    delta2DVisualizer->Y = ui->leYValue->text().toFloat();
    delta2DVisualizer->Z = ui->leZValue->text().toFloat();

    if(delta2DVisualizer->Z > -200){
        delta2DVisualizer->Z = -200;
        ui->leZValue->setText("-200");
    }else if(delta2DVisualizer->Z < -500){
        delta2DVisualizer->Z = -500;
        ui->leZValue->setText("-500");
    }

    ui->lbX->setText(QString::number(delta2DVisualizer->X));
    ui->lbY->setText(QString::number(delta2DVisualizer->Y));
    ui->lbZ->setText(QString::number(delta2DVisualizer->Z));

    ui->sldZAdjustion->setValue(delta2DVisualizer->ZHome - delta2DVisualizer->Z);
    delta2DVisualizer->changeXY(delta2DVisualizer->X, delta2DVisualizer->Y);

    updateDeltaPositionFromGUI();
}

void MainWindow::updateDeltaPositionFromGUI()
{
    m_connection->sendData(QString("G01 X") + ui->lbX->text() + QString(" Y") + ui->lbY->text() + QString(" Z") + ui->lbZ->text() + "\n");
}

void MainWindow::turnOnConveyor()
{
    m_connection->sendData(QString("M300"));
}

void MainWindow::turnOffConveyor()
{
    m_connection->sendData(QString("M301"));
}

void MainWindow::setSpeedForConveyor()
{
    m_connection->sendData(QString("M302 ") + ui->leSpeedConveyor->text());
}

void MainWindow::updateInfor_LoadCamera()
{
    bool camOnOff = ui->btnLoadCam->isChecked();

    deltaImageProcessor->idCamera = ui->leIDCam->text().toInt();
    deltaImageProcessor->cameraFPS = ui->leFPS->text().toInt();


    deltaImageProcessor->loadCamera(camOnOff);
}

void MainWindow::changeModeDisplay()
{
    ui->lblCam->calibMode = false;
    if(ui->cmbModeDisplay->currentText() == "Normal"){
        deltaImageProcessor->imgMode = deltaImageProcessor->ORIGIN;
        deltaImageProcessor->openParameterPanel(false);
    }else if(ui->cmbModeDisplay->currentText() == "Processing"){
        deltaImageProcessor->imgMode = deltaImageProcessor->HSV_PROCESSEING;
        deltaImageProcessor->openParameterPanel(true);
    }else if(ui->cmbModeDisplay->currentText() == "Result"){
        deltaImageProcessor->imgMode = deltaImageProcessor->RESULT;
        deltaImageProcessor->openParameterPanel(false);
    }else if(ui->cmbModeDisplay->currentText() == "Calibration"){
        deltaImageProcessor->imgMode = deltaImageProcessor->CALIB;
        deltaImageProcessor->openParameterPanel(false);
        ui->lblCam->calibMode = true;
    }
    ui->lblCam->calibModeUpdate();
}

void MainWindow::executeProgram()
{
    QPushButton *pbExe = qobject_cast<QPushButton*>(sender());

    if(pbExe->isChecked()){

        ui->gbMotionControl->setDisabled(true);
        ui->gbConnection->setDisabled(true);

        saveProgram();

        QString exeGcodes = gcodeView->teGcodeWidget->toPlainText();
        deltaGcodeManager->executeGcode(exeGcodes);
    }else{
        ui->gbMotionControl->setDisabled(false);
        ui->gbConnection->setDisabled(false);

        deltaGcodeManager->stop();
    }
}

void MainWindow::saveProgram(){
    QString proName = gcodeView->cmbProgramList->currentText();
    proName = proName.replace(" ", "");
    deltaGcodeManager->saveGcodeIntoFile(proName);
}

void MainWindow::loadProgram()
{
    QString proName = gcodeView->cmbProgramList->currentText();
    if(proName == "") return;
    proName = proName.replace(" ", "");
    deltaGcodeManager->loadProgram(proName);
}

void MainWindow::activateVacuum()
{
    QPushButton *btnvac = qobject_cast<QPushButton*>(sender());

    if(btnvac->isChecked()){
        //Turn on conveyor
        m_connection->sendData("M05");
    }else{
        //Turn off conveyor
        m_connection->sendData("M04");
    }
}

void MainWindow::changeCalibTool()
{
    QPushButton *bt = qobject_cast<QPushButton*>(sender());

    if(bt == ui->btnLine){
        if(ui->btnLine->isChecked()) ui->lblCam->selectedCalibTool = CalibTool::LINE;
        else ui->lblCam->selectedCalibTool = CalibTool::NONE;

        if(ui->btnRectangle->isChecked()) ui->btnRectangle->setChecked(false);
        if(ui->btnPoint->isChecked()) ui->btnPoint->setChecked(false);
    }else if(bt == ui->btnRectangle){
        if(ui->btnRectangle->isChecked()) ui->lblCam->selectedCalibTool = CalibTool::RECTANGLE;
        else ui->lblCam->selectedCalibTool = CalibTool::NONE;

        if(ui->btnLine->isChecked()) ui->btnLine->setChecked(false);
        if(ui->btnPoint->isChecked()) ui->btnPoint->setChecked(false);
    }else if(bt == ui->btnPoint){
        if(ui->btnPoint->isChecked()) ui->lblCam->selectedCalibTool = CalibTool::POINT;
        else ui->lblCam->selectedCalibTool = CalibTool::NONE;

        if(ui->btnRectangle->isChecked()) ui->btnRectangle->setChecked(false);
        if(ui->btnLine->isChecked()) ui->btnLine->setChecked(false);
    }

}










