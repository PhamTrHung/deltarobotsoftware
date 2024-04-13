#include "camerawidget.h"
#include <QDebug>

CameraWidget::CameraWidget(QWidget *parent):
    QLabel(parent)
{
    mousePressed = false;


    initParameter();
}

void CameraWidget::initParameter()
{
    mLine.setP1(QPoint(100, 20));
    mLine.setP2(QPoint(100, 100));

    mPoint = QPoint(150, 150);

    mRect.setRect(150, 150, 100, 100);

    emit finishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit finishSelectCalibLine(mLine.p1(), mLine.p2());
    emit finishSelectCalibPoint(mPoint.x(), mPoint.y());
    emit finishSelectProcessArea(mRect);

    update();
}

void CameraWidget::calibModeUpdate()
{
    update();
}

void CameraWidget::mousePressEvent(QMouseEvent *event)
{
    
    if(!calibMode) return;

    if(selectedCalibTool == RECTANGLE){
        rectPointPosClicked = -1;
        if(abs(mRect.topLeft().x() - event->pos().x()) < 5 &&
            abs(mRect.topLeft().y() - event->pos().y()) < 5){
            rectPointPosClicked = 1;
        }
        if(abs(mRect.bottomRight().x() - event->pos().x()) < 5 &&
            abs(mRect.bottomRight().y() - event->pos().y()) < 5){
            rectPointPosClicked = 2;
        }

    }else if(selectedCalibTool == LINE){
        linePointPosClicked = -1;
        if(abs(mLine.p1().x() - event->pos().x()) < 5 &&
            abs(mLine.p1().y() - event->pos().y()) < 5 ){
            linePointPosClicked = 1;
        }

        if(abs(mLine.p2().x() - event->pos().x()) < 5 &&
            abs(mLine.p2().y() - event->pos().y()) < 5 ){
            linePointPosClicked = 2;
        }

    }else if(selectedCalibTool == POINT){
        mPoint = event->pos();
    }

    mousePressed = true;
    update();
}

void CameraWidget::mouseMoveEvent(QMouseEvent *event)
{

    if(!calibMode) return;

    if(event->type() == QEvent::MouseMove){
        if(selectedCalibTool == RECTANGLE){
            if(rectPointPosClicked == 1) mRect.setTopLeft(event->pos());
            if(rectPointPosClicked == 2) mRect.setBottomRight(event->pos());
        }else if(selectedCalibTool == LINE){
            if(linePointPosClicked == 1) mLine.setP1(event->pos());
            if(linePointPosClicked == 2) mLine.setP2(event->pos());
        }else if(selectedCalibTool == POINT){
            mPoint = event->pos();
        }
    }

    update();
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(!calibMode) return;

    emit finishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit finishSelectCalibLine(mLine.p1(), mLine.p2());
    emit finishSelectCalibPoint(mPoint.x(), mPoint.y());
    emit finishSelectProcessArea(mRect);

    mousePressed = false;
    update();
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    painter.begin(this);
    painter.setPen(QPen(Qt::red, 3));

    if(calibMode == true){
        painter.drawRect(mRect);
        painter.drawRect(mRect.topLeft().x() - 2, mRect.topLeft().y() - 2, 4, 4);
        painter.drawRect(mRect.bottomRight().x() - 2, mRect.bottomRight().y() - 2, 4, 4);

        painter.drawLine(mLine);
        painter.drawRect(mLine.p1().x() - 2, mLine.p1().y() - 2, 4, 4);
        painter.drawRect(mLine.p2().x() - 2, mLine.p2().y() - 2, 4, 4);

        painter.drawPoint(mPoint);
    }

    painter.end();

}














