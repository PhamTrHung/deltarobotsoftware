#ifndef DELTAVISUALIZER_H
#define DELTAVISUALIZER_H

#include <QLabel>
#include <QMouseEvent>
#include <QElapsedTimer>
#include <QComboBox>
#include <QPainter>
#include <QPixmap>

#define MOVING_BASE_SIZE 50

class DeltaVisualizer : public QLabel
{
    Q_OBJECT

public:
    DeltaVisualizer(QWidget* parent = 0);
    ~DeltaVisualizer();

    void moveToHome();
    //void initGrid();

    void setDivisionCombobox(QComboBox* d);

    float XHome = 0;
    float YHome = 0;
    float ZHome = -200;
    float VDefault = 200;
    float ADefault = 1200;

    float X = XHome;
    float Y = YHome;
    float Z = ZHome;
    float V = VDefault;
    float A = ADefault;

public slots:
    void changeXY(int x, int y);
    void moveUp();
    void moveDown();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();

signals:
    void moved(float x, float y, float z);
    void cursorMoved();
    void finishMoving();

    void upArrow();
    void downArrow();
    void leftArrow();
    void rightArrow();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    bool eventFilter(QObject* dist, QEvent* event);

private:
    QElapsedTimer timer;

    QComboBox* cbDivision;

    float fPara;
    float rfPara;
    float rePara;
    float ePara;

};

#endif // DELTAVISUALIZER_H
