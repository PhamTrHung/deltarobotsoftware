#ifndef GCODEPROGRAMMANAGER_H
#define GCODEPROGRAMMANAGER_H

#include <QObject>
#include <QTextEdit>
#include <QPushButton>
#include <QFile>
#include <QDir>

#include "connectionmanager.h"

class GcodeVariable{
public:
    QString name;
    float value;
};

#define NULL_NUMBER -6789

class GcodeProgramManager : public QObject
{
    Q_OBJECT
public:
    explicit GcodeProgramManager(QObject *parent = nullptr);
    ~GcodeProgramManager();
    GcodeProgramManager(QTextEdit* gcodeArea, QPushButton* btnExecute, ConnectionManager* deltaSerialPort);
    void addG01(float x, float y, float z);
    void addG28();
    void addM204(float accel);
    void executeGcode(QString gcode);
    void stop();
    void loadProgram(QString fileName);


    QTextEdit* teGcodeArea;
    QPushButton* btnExecuteGcodes;
    ConnectionManager* deltaConnection;

public slots:
    void addGcodeLine(QString line);
    void updateSystemVariable(QString name, float value);
    void transmitNextGcode();
    void saveGcodeIntoFile(QString fileName);

signals:
    void outOfObjectVariable();
    void deleteAllObjects();
    void deleteFirstObject();
    void pauseCamera();
    void captureCamera();
    void resumeCamera();

    void justUpdateVariable(QList<GcodeVariable> gcodevariables);
    void moveToNewPosition(float x, float y, float z, float f, float a);

private:
    QList<QString> gcodeList;
    QList<GcodeVariable> gcodeVariables;
    int currentGcodeEditorCursor = 0;
    int gcodeOrder = 0;
    QString currentLine;
    int returnPointerIndex = -1;
    int returnSubProPointer[20];
    QString startMode = "Begin";


    float getVariableValue(QString name);
    bool isGlobalVariable(QString name);
    bool isMovingGcode(QString gcode);
    bool findExeGcodeAndTransmit();
    float calculateExpression(QString expression);
    void saveGcodeVaribale(GcodeVariable gvar);
    void saveGcodeVaribale(QString name, float value);
    void updatePositionIntoSystemVariable(QString statement);
    QString getLeftWord(QString s, int pos);
    QString getRightWord(QString s, int pos);
    QString deleteSpaces(QString s);
    bool isNotNegative(QString s);

};

#endif // GCODEPROGRAMMANAGER_H
