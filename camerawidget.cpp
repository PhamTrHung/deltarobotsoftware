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
    mLine.setP1(QPoint(100, 50));
    mLine.setP2(QPoint(200, 50));

    mPoint = QPoint(150, 150);

    mRect.setRect(150, 150, 100, 100);

    transformPoints[0] = QPoint(100, 100);
    transformPoints[1] = QPoint(100, 200);
    transformPoints[2] = QPoint(200, 200);
    transformPoints[3] = QPoint(200, 100);

    emit finishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit finishSelectCalibLine(mLine.p1(), mLine.p2());
    emit finishSelectCalibPoint(mPoint.x(), mPoint.y());
    emit finishSelectProcessArea(mRect);
    emit finishSelectedTransformPoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);

    update();
}

void CameraWidget::calibModeUpdate()
{
    update();
}

void CameraWidget::changeSize(int w, int h)
{
    float wRatio = (float)w / geometry().width();
    float hRatio = (float)h / geometry().height();

    mLine.setLine(mLine.x1() * wRatio, mLine.y1() * hRatio, mLine.x2() * wRatio, mLine.y2() * hRatio);

    mPoint.setX(mPoint.x() * wRatio);
    mPoint.setY(mPoint.y() * hRatio);

    mRect.setRect(mRect.x() * wRatio, mRect.y() * hRatio, mRect.width() * wRatio, mRect.height() * hRatio);

    transformPoints[0].setX(transformPoints[0].x() * wRatio);
    transformPoints[0].setY(transformPoints[0].y() * hRatio);
    transformPoints[1].setX(transformPoints[1].x() * wRatio);
    transformPoints[1].setY(transformPoints[1].y() * hRatio);
    transformPoints[2].setX(transformPoints[2].x() * wRatio);
    transformPoints[2].setY(transformPoints[2].y() * hRatio);
    transformPoints[3].setX(transformPoints[3].x() * wRatio);
    transformPoints[3].setY(transformPoints[3].y() * hRatio);


    QRect size = geometry();
    size.setWidth(w);
    size.setHeight(h);
    setGeometry(size);

    QRect parentSize = parentWidget()->geometry();
    parentSize.setWidth(w);
    parentSize.setHeight(h);
    parentWidget()->setGeometry(parentSize);

    emit sizeChange();

    emit finishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit finishSelectCalibLine(mLine.p1(), mLine.p2());
    emit finishSelectCalibPoint(mPoint.x(), mPoint.y());
    emit finishSelectProcessArea(mRect);
    emit finishSelectedTransformPoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
}

void CameraWidget::saveSetting()
{
    QSettings settings("setting.ini", QSettings::IniFormat);

    settings.setValue("line", mLine);
    settings.setValue("rect", mRect);
    settings.setValue("point", mPoint);
    settings.setValue("transpoint1", transformPoints[0]);
    settings.setValue("transpoint2", transformPoints[1]);
    settings.setValue("transpoint3", transformPoints[2]);
    settings.setValue("transpoint4", transformPoints[3]);
}

void CameraWidget::loadSetting()
{
    QSettings settings("setting.ini", QSettings::IniFormat);

    mLine = settings.value("line").toLine();

    mRect = settings.value("rect").toRect();

    mPoint = settings.value("point").toPoint();

    transformPoints[0] = settings.value("transpoint1").toPoint();
    transformPoints[1] = settings.value("transpoint2").toPoint();
    transformPoints[2] = settings.value("transpoint3").toPoint();
    transformPoints[3] = settings.value("transpoint4").toPoint();

    emit finishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit finishSelectCalibLine(mLine.p1(), mLine.p2());
    emit finishSelectCalibPoint(mPoint.x(), mPoint.y());
    emit finishSelectProcessArea(mRect);
    emit finishSelectedTransformPoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
}

void CameraWidget::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << mRect.x();
    //qDebug() << mRect.y();
    
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

        transformOrder = -1;
        for (int i = 0; i < 4; ++i) {
            if(abs(transformPoints[i].x() - event->pos().x()) < 5 &&
                abs(transformPoints[i].y() - event->pos().y()) < 5) {
                transformOrder = i;
                break;
            }
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
            if (rectPointPosClicked == 1) {
                mRect.setTopLeft(event->pos());
                emit finishSelectProcessArea(mRect);
            }
            if (rectPointPosClicked == 2) {
                mRect.setBottomRight(event->pos());
                emit finishSelectProcessArea(mRect);
            }
            if (transformOrder != -1) {
                transformPoints[transformOrder] = event->pos();
                emit finishSelectedTransformPoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
            }
        }else if(selectedCalibTool == LINE){
            if (linePointPosClicked == 1) {
                mLine.setP1(event->pos());
                emit finishSelectCalibLine(mLine.p1(), mLine.p2());
            }
            if (linePointPosClicked == 2) {
                mLine.setP2(event->pos());
                emit finishSelectCalibLine(mLine.p1(), mLine.p2());
            }
        }else if(selectedCalibTool == POINT){
            mPoint = event->pos();
            emit finishSelectCalibPoint(mPoint.x(), mPoint.y());
        }
    }

    update();
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(!calibMode) return;

    emit finishMeasureSpace(sqrt(pow(mLine.x1() - mLine.x2(), 2) + pow(mLine.y1() - mLine.y2(), 2)));
    emit finishSelectCalibLine(mLine.p1(), mLine.p2());
    emit finishSelectProcessArea(mRect);
    emit finishSelectedTransformPoints(transformPoints[0], transformPoints[1], transformPoints[2], transformPoints[3]);
    emit finishSelectCalibPoint(mPoint.x(), mPoint.y());

    mousePressed = false;
    update();
}

void CameraWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    painter.begin(this);
    painter.setPen(QPen(Qt::red, 3));

    painter.drawPoint(mapFromGlobal(QCursor::pos()));

    if(calibMode == true){
        /*painter.drawRect(mRect);
        painter.drawRect(mRect.topLeft().x() - 2, mRect.topLeft().y() - 2, 4, 4);
        painter.drawRect(mRect.bottomRight().x() - 2, mRect.bottomRight().y() - 2, 4, 4);

        painter.drawLine(mLine);
        painter.drawRect(mLine.p1().x() - 2, mLine.p1().y() - 2, 4, 4);
        painter.drawRect(mLine.p2().x() - 2, mLine.p2().y() - 2, 4, 4);

        painter.drawPoint(mPoint);*/

        /*painter.drawPoint(transformPoints[0]);
        painter.drawPoint(transformPoints[1]);
        painter.drawPoint(transformPoints[2]);
        painter.drawPoint(transformPoints[3]);*/
    }

    painter.end();

}














