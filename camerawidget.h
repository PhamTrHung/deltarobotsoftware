#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <qmath.h>

enum CalibTool{
    NONE,
    LINE,
    POINT,
    RECTANGLE,
};

class CameraWidget : public QLabel
{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = 0);

    void initParameter();

    bool calibMode = false;
    void calibModeUpdate();
    CalibTool selectedCalibTool = CalibTool::NONE;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //Moi lan co update la goi ra ham paintEvent
    void paintEvent(QPaintEvent *event);

signals:
    void finishMeasureSpace(int distance);
    void finishSelectCalibLine(QPoint a, QPoint b);
    void finishSelectCalibPoint(int x, int y);
    void finishSelectProcessArea(QRect rect);

private:
    QPainter painter;
    QLine mLine;
    QPixmap mPix;
    QRect mRect;
    QPoint mPoint;

    int rectPointPosClicked = 0;
    int linePointPosClicked = 0;

    bool mousePressed;


};

#endif // CAMERAWIDGET_H
