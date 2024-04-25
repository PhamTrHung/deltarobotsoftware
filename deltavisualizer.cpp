#include "deltavisualizer.h"
#include <QDebug>

DeltaVisualizer::DeltaVisualizer(QWidget *parent): QLabel(parent)
{
    setMouseTracking(true);
}

DeltaVisualizer::~DeltaVisualizer()
{

}

void DeltaVisualizer::moveToHome()
{
    emit moved(XHome, YHome, ZHome);
    emit finishMoving();
}

void DeltaVisualizer::setDivisionCombobox(QComboBox *d)
{
    cbDivision = d;
}

void DeltaVisualizer::changeXY(int x, int y)
{
    if (x > X_MAX) x = X_MAX;
    else if (x < X_MIN) x = X_MIN;

    if (y > Y_MAX) y = Y_MAX;
    else if (y < Y_MIN) y = Y_MIN;

    QPixmap pi = QPixmap(width(), height());
    pi.fill(QColor(0, 0, 0, 200));

    QPixmap pix = QPixmap(QString::fromUtf8(":/icons/triangle.png"));

    QPainter p(&pi);

    //p.begin(this);

    p.drawPixmap(width()/2 + x - MOVING_BASE_SIZE/2, height()/2 - MOVING_BASE_SIZE/2 - y, MOVING_BASE_SIZE, MOVING_BASE_SIZE, pix);

    //draw a cicle express limit area
    p.setPen(QColor(255,255,102,170));
    p.drawEllipse(width()/2 - 150, height()/2 - 150, 300, 300);


    p.end();

    setPixmap(pi);
    setScaledContents(true);

    update();

    X = x;
    Y = y;
}


void DeltaVisualizer::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x() - width()/2;
    int y = -event->pos().y() + height()/2;

    changeXY(x, y);

    emit moved(X, Y, Z);
}

void DeltaVisualizer::mouseReleaseEvent(QMouseEvent *event)
{
    emit finishMoving();
}

void DeltaVisualizer::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        changeXY(event->pos().x() - width()/2, -event->pos().y() + height()/2);
        emit moved(X, Y, Z);
    }
}

bool DeltaVisualizer::eventFilter(QObject *dist, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        float division = cbDivision->currentText().toFloat();

        if(QString("1234567890").indexOf(keyEvent->text()) == -1){
            return true;
        }else if(keyEvent->key() == Qt::Key_Up){
            emit upArrow();
            Y += division;
        }else if(keyEvent->key() == Qt::Key_Down){
            emit downArrow();
            Y -= division;
        }else if(keyEvent->key() == Qt::Key_Left){
            emit leftArrow();
            X -= division;
        }else if(keyEvent->key() == Qt::Key_Right){
            emit rightArrow();
            X += division;
        }

        emit moved(X,Y,Z);
        emit finishMoving();
        return true;
    }
    return false;
}


void DeltaVisualizer::moveUp()
{
    float division = cbDivision->currentText().toFloat();
    Z += division;

    if(Z > Z_MAX) Z = Z_MAX;

    emit moved(X,Y,Z);
    emit finishMoving();
}

void DeltaVisualizer::moveDown()
{
    float division = cbDivision->currentText().toFloat();
    Z -= division;

    if(Z < Z_MIN) Z = Z_MIN;

    emit moved(X,Y,Z);
    emit finishMoving();
}

void DeltaVisualizer::moveForward()
{
    float division = cbDivision->currentText().toFloat();
    X += division;

    if (X > X_MAX) X = X_MAX;
    changeXY(X,Y);

    emit moved(X,Y,Z);
    emit finishMoving();
}

void DeltaVisualizer::moveBackward()
{
    float division = cbDivision->currentText().toFloat();
    X -= division;

    if (X < X_MIN) X = X_MIN;
    changeXY(X,Y);


    emit moved(X,Y,Z);
    emit finishMoving();
}

void DeltaVisualizer::moveLeft()
{
    float division = cbDivision->currentText().toFloat();
    Y += division;

    if (Y > Y_MAX) Y = Y_MAX;
    changeXY(X,Y);

    emit moved(X,Y,Z);
    emit finishMoving();
}

void DeltaVisualizer::moveRight()
{
    float division = cbDivision->currentText().toFloat();
    Y -= division;

    if (Y < Y_MIN) Y = Y_MIN;
    changeXY(X,Y);

    emit moved(X,Y,Z);
    emit finishMoving();
}






