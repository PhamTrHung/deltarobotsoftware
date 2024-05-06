#include "imageprocessor.h"
#include <QDebug>


ImageProcessor::ImageProcessor(QWidget *parent)
    :QWidget(parent)
{
    //mParent = parent;

    parameterPanel = new HSVWindow(parent);
    connect(parameterPanel, SIGNAL(valueChanged(int,int,int,int,int,int)),
            this, SLOT(setHSV(int,int,int,int,int,int)));
    connect(parameterPanel, SIGNAL(addObject(int, QString)), this, SLOT(getObjectsInfor(int, QString)));

    camera = new cv::VideoCapture();

    updateScreenTimer = new QTimer(this);
    connect(updateScreenTimer, SIGNAL(timeout()), this, SLOT(updateCameraScreen()));
    updateScreenTimer->start(cameraTimerInterval);

    obManager = new ObjectManager(parent);

    timerTool.start();
}

ImageProcessor::~ImageProcessor()
{
    if(camera->isOpened())
        camera->release();
    delete parameterPanel;
}

QImage ImageProcessor::convertMatToImg(cv::Mat mat)
{
    if(mat.channels() == 1){
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    }else if(mat.channels() == 3){
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    }else{
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }

    return QImage();
}

void ImageProcessor::updateLabelImage(cv::Mat mat, QLabel *label)
{
    QImage img = convertMatToImg(mat);

    //cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    //QImage img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

    label->setPixmap(QPixmap::fromImage(img));
    label->setScaledContents(true);
    //label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void ImageProcessor::setImageScreen(CameraWidget *screen)
{
    lbResultImage = screen;
}

void ImageProcessor::setObjectInforLabelWidget(QLabel* lbTracking, QLabel* lbVisible, QLabel* obj1Name, QLabel* obj2Name,
    QLabel* obj3Name, QLabel* obj1Number, QLabel* obj2Number, QLabel* obj3Number)
{
    lbTrackingObjectNumber = lbTracking;
    lbVisibleObjectNumber = lbVisible;
    lbObject1Name = obj1Name;
    lbObject2Name = obj2Name;
    lbObject3Name = obj3Name;
    lbObject1Number = obj1Number;
    lbObject2Number = obj2Number;
    lbObject3Number = obj3Number;
}

void ImageProcessor::setMeasureParameterPointer(QLineEdit *xCoor, QLineEdit *yCoor, QLineEdit *distance)
{
    leDistance = distance;
    leXCoor = xCoor;
    leYCoor = yCoor;
}

void ImageProcessor::getPerspectivePoints(QPoint p1, QPoint p2, QPoint p3, QPoint p4)
{
    DPerspectivePoints[0] = p1;
    DPerspectivePoints[1] = p2;
    DPerspectivePoints[2] = p3;
    DPerspectivePoints[3] = p4;

    PPerspectivePoints.clear();
    PPerspectivePoints.push_back(cv::Point(p1.x() / DnPWRatio, p1.y() / DnPHRatio));
    PPerspectivePoints.push_back(cv::Point(p2.x() / DnPWRatio, p2.y() / DnPHRatio));
    PPerspectivePoints.push_back(cv::Point(p3.x() / DnPWRatio, p3.y() / DnPHRatio));
    PPerspectivePoints.push_back(cv::Point(p4.x() / DnPWRatio, p4.y() / DnPHRatio));
}

void ImageProcessor::turnOnPerspectiveMode()
{
    isPerspectiveMode = true;
}

void ImageProcessor::turnOffPerspectiveMode()
{
    isPerspectiveMode = false;
}

void ImageProcessor::displayAdditionalInfor()
{
    if (calibImage.empty()) return;

    int offset = 1;
    int thin = 1;

    //draw process rectangle
    drawBlackWhiteRect(calibImage, PSelectedRect);
    drawCorner(calibImage, cv::Point(PSelectedRect.x, PSelectedRect.y));
    drawCorner(calibImage, cv::Point(PSelectedRect.x + PSelectedRect.width, PSelectedRect.y + PSelectedRect.height));

    //Draw perspective area
    /*if (!isPerspectiveMode) {
        if (DPerspectivePoints != NULL) {
            for (int i = 0; i < 3; ++i) {
                drawBlackWhiteLine(calibImage, PPerspectivePoints[i], PPerspectivePoints[i + 1], thin);
                drawCorner(calibImage, PPerspectivePoints[i]);
            }
            drawBlackWhiteLine(calibImage, PPerspectivePoints[3], PPerspectivePoints[0], thin);
            drawCorner(calibImage, PPerspectivePoints[3]);
        }
    }*/
    
    //Point
    cv::rectangle(calibImage, cv::Rect(PcalibPoint.x - 2, PcalibPoint.y - 2, 5, 5), WHITE_COLOR, cv::FILLED);
    cv::putText(calibImage, std::string("x = ") + leXCoor->text().toStdString() + ", y = " + leYCoor->text().toStdString(), cv::Point(PcalibPoint.x, PcalibPoint.y - 10), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(255, 255, 0), 1);
    //Line
    drawLine(calibImage, cv::Point(DCalibLine.p1().x() / DnPWRatio, DCalibLine.p1().y() / DnPHRatio), cv::Point(DCalibLine.p2().x() / DnPWRatio, DCalibLine.p2().y() / DnPHRatio));
    cv::rectangle(calibImage, cv::Rect(DCalibLine.p1().x() / DnPWRatio - 2, DCalibLine.p1().y() / DnPHRatio - 2, 3, 3), WHITE_COLOR, cv::FILLED);
    cv::rectangle(calibImage, cv::Rect(DCalibLine.p2().x() / DnPWRatio - 2, DCalibLine.p2().y() / DnPHRatio - 2, 3, 3), WHITE_COLOR, cv::FILLED);
    cv::putText(calibImage, leDistance->text().toStdString() + " mm", cv::Point(DCalibLine.center().x() / DnPWRatio - 5, DCalibLine.center().y() / DnPHRatio - 10), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(255, 255, 0), 1);
}

void ImageProcessor::loadCamera(bool state)
{
    if(state){

        if(cameraFPS >= 15 && cameraFPS <= 30){
            updateScreenTimer->stop();
            cameraTimerInterval = 1000/cameraFPS;
            updateScreenTimer->start(cameraTimerInterval);
        }
        
        lbResultImage->initParameter();

        camera->open(idCamera, cv::CAP_DSHOW);
        camera->set(cv::CAP_PROP_FRAME_WIDTH, 800);
        camera->set(cv::CAP_PROP_FRAME_HEIGHT, 600);

        updateRatios();

        isCameraPause = false;
    }else{
        updateLabelImage(cv::Mat(cv::Size(lbResultImage->width(), lbResultImage->height()), CV_8UC3, cv::Scalar( 0, 0, 0)), lbResultImage);
        isCameraPause = true;
        camera->release();
        return;
    }
}

void ImageProcessor::updateCameraScreen()
{
    if(isCameraPause == false){
        captureCamera();
    }

}

void ImageProcessor::captureCamera()
{
    if(!camera->isOpened())
        return;

    camera->read(captureImage);

    processImage();

    updateObjectPositionOnConveyor();
}

void ImageProcessor::getImgFromThread(cv::Mat*)
{

}

void ImageProcessor::saveImage()
{
    if(!captureImage.empty() && camera->isOpened()){
        QString path = QString("E:/DoAnTotNghiep/Program/Qt_app/DeltaRobotSoftware/DeltaRobotSoftware/capture/pic%1.png").arg(imageCapturedNumber++);

        if(imgMode == ORIGIN){
            cv::cvtColor(captureImage, captureImage, cv::COLOR_BGR2RGB);
            cv::imwrite(path.toStdString(), captureImage);
        }else if(imgMode == HSV_PROCESSEING){
            cv::imwrite(path.toStdString(), HSV_CaptureImage);
        }else if(imgMode == RESULT){
            cv::cvtColor(resultImage, resultImage, cv::COLOR_BGR2RGB);
            cv::imwrite(path.toStdString(), resultImage);
        }
    }
}

void ImageProcessor::openParameterPanel(bool isOpened)
{
    //parameterPanel->exec();
    if(isOpened) parameterPanel->show();
    else parameterPanel->close();

}

void ImageProcessor::setHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV)
{
    HSV_Value[0] = minH;
    HSV_Value[1] = maxH;
    HSV_Value[2] = minS;
    HSV_Value[3] = maxS;
    HSV_Value[4] = minV;
    HSV_Value[5] = maxV;
}

void ImageProcessor::getObjectsInfor(int numberObject, QString nameObject)
{
    if (numberObject == 1) {
        nameObjectInfor[numberObject - 1] = nameObject;
        for (uint8_t i = 0; i < 6; ++i) {
            HSV_OBJECT[numberObject - 1][i] = HSV_Value[i];
        }
    }
    else if (numberObject == 2) {
        nameObjectInfor[numberObject - 1] = nameObject;
        for (uint8_t i = 0; i < 6; ++i) {
            HSV_OBJECT[numberObject - 1][i] = HSV_Value[i];
        }
    }
    else if (numberObject == 3) {
        nameObjectInfor[numberObject - 1] = nameObject;
        for (uint8_t i = 0; i < 6; ++i) {
            HSV_OBJECT[numberObject - 1][i] = HSV_Value[i];
        }
    }
}

void ImageProcessor::getCalibPoint(int x, int y)
{
    DCalibPoint.setX(x);
    DCalibPoint.setY(y);

    if (captureImage.cols > 0) {
        PcalibPoint.x = x / DnPWRatio;
        PcalibPoint.y = y / DnPHRatio;
    }

    if (leXCoor == nullptr) return;

    //qDebug() << "DnPWRatio = " << DnPWRatio;
    //qDebug() << "DnPHRatio = " << DnPHRatio;

    //qDebug() << "x = " << x;
    //qDebug() << "y = " << y;

    float xRealCalibPoint = leXCoor->text().toFloat();
    float yRealCalibPoint = leYCoor->text().toFloat();

    //qDebug() << "xreal = " << xRealCalibPoint;
    //qDebug() << "yreal = " << yRealCalibPoint;

    // X axis
    // góc giữa hệ tọa độ vật so với hệ tọa độ robot delta
    float theta = 0;

    cv::Mat rotateMatrix = (cv::Mat_<float>(3, 3) << cos(theta), -sin(theta), 0,
                                                     sin(theta), cos(theta), 0,
                                                     0, 0, 1);

    cv::Mat scaleMatrix = (cv::Mat_<float>(3, 3) << 1.0f / PnRRatio, 0, 0,
                                                    0, -1.0f / PnRRatio, 0,
                                                    0, 0, 1);
    //qDebug() << "PnRRatio = " << PnRRatio;
    
    cv::Mat scaleRotateMatrix = scaleMatrix * rotateMatrix ;
    //qDebug() << scaleRotateMatrix.at<float>(2, 2);

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float dx = xRealCalibPoint - (scaleRotateMatrix.at<float>(0, 0) * (PcalibPoint.x) + scaleRotateMatrix.at<float>(1, 0) * (PcalibPoint.y));
    float dy = yRealCalibPoint - (scaleRotateMatrix.at<float>(0, 1) * (PcalibPoint.x) + scaleRotateMatrix.at<float>(1, 1) * (PcalibPoint.y));

    P2RMatrix = (cv::Mat_<float>(3, 3) << scaleRotateMatrix.at<float>(0, 0), scaleRotateMatrix.at<float>(1, 0), dx,
                                          scaleRotateMatrix.at<float>(0, 1), scaleRotateMatrix.at<float>(1, 1), dy,
                                          0, 0, 1);

    cv::Mat result = P2RMatrix * (cv::Mat_<float>(3, 1) << PcalibPoint.x, PcalibPoint.y, 1);
    //qDebug() << "result x = " << result.at<float>(0, 0);
    //qDebug() << "result y = " << result.at<float>(1, 0);
    //qDebug() << result.at<float>(2, 0);
}

void ImageProcessor::getDistance(int distance)
{
    float realDistance = leDistance->text().toFloat();

    float processDistance = processDistanceValue;
    
    //qDebug() << "real distance = " << realDistance;
    //qDebug() << "process distance = " << processDistance;

    PnRRatio = processDistance / realDistance;
    DnRRatio = (float)distance / realDistance;

    
}

void ImageProcessor::getProcessArea(QRect processArea)
{
    
    DSelectedRect = processArea;

    PSelectedRect.width = processArea.width() / DnPWRatio;
    PSelectedRect.height = processArea.height() / DnPHRatio;
    PSelectedRect.x = processArea.x() / DnPWRatio;
    PSelectedRect.y = processArea.y() / DnPHRatio;

}

void ImageProcessor::getCalibLine(QPoint p1, QPoint p2)
{
    DCalibLine.setP1(p1);
    DCalibLine.setP2(p2);

    QLineF line;
    line.setP1(QPointF(p1.x() / DnPWRatio, p1.y() / DnPHRatio));
    line.setP2(QPointF(p2.x() / DnPWRatio, p2.y() / DnPHRatio));
    //qDebug() << "Line p1: x " << line.p1().x() << " y " << line.p1().y();
    //qDebug() << "Line p2: x " << line.p2().x() << " y " << line.p2().y();
    //qDebug() << "real distance process = " << line.length();
    processDistanceValue = line.length();
}

void ImageProcessor::processImage()
{
    if(!captureImage.data){
        return;
    }

    captureImage.copyTo(originalImage);

    //Copy to calib image
    captureImage.copyTo(calibImage);
    //if (isPerspectiveMode) transformPerspective(calibImage, PPerspectivePoints, calibImage);

    //Filter image
    HSV_CaptureImage = captureImage.clone();
    cv::cvtColor(HSV_CaptureImage, HSV_CaptureImage, cv::COLOR_BGR2HSV);
    for (uint8_t i = 0; i < 3; ++i) {
            HSV_CaptureImage.copyTo(objectImage[i]);
    }

    cv::Scalar minScalar(HSV_Value[0], HSV_Value[2], HSV_Value[4]);
    cv::Scalar maxScalar( HSV_Value[1],HSV_Value[3],HSV_Value[5]);

    cv::inRange(HSV_CaptureImage, minScalar, maxScalar, HSV_CaptureImage);

    selectProcessingRegion(HSV_CaptureImage);


    //detect objects in image
    captureImage.copyTo(resultImage);
    //detectObject(HSV_CaptureImage, resultImage, BLUE_COLOR, "Blue");

    //reset visiableCounter
    visibleCounter = 0;
    for (uint8_t i = 0; i < 3; i++) {

        minScalar = cv::Scalar(HSV_OBJECT[i][0], HSV_OBJECT[i][2], HSV_OBJECT[i][4]);
        maxScalar = cv::Scalar(HSV_OBJECT[i][1], HSV_OBJECT[i][3], HSV_OBJECT[i][5]);

        cv::inRange(objectImage[i], minScalar, maxScalar, objectImage[i]);
        selectProcessingRegion(objectImage[i]);
        
        detectObject(objectImage[i], resultImage, BLUE_COLOR, nameObjectInfor[i], i);
    }

    //Update object tracking infor
    updateTrackingInfor();

    //display

    if(imgMode == ORIGIN){
        updateLabelImage(originalImage, lbResultImage);
    }else if(imgMode == HSV_PROCESSEING){
        updateLabelImage(HSV_CaptureImage, lbResultImage);
    }else if(imgMode == RESULT){
        updateLabelImage(resultImage, lbResultImage);
    }else if (imgMode == CALIB) {
        makeBrightProcessRegion(calibImage);
        displayAdditionalInfor();
        updateLabelImage(calibImage, lbResultImage);
    }
}

void ImageProcessor::detectObject(cv::Mat input, cv::Mat output, cv::Scalar color, QString TextDisplay, int objNum)
{
    //Find contour in image
    std::vector<std::vector<cv::Point>> contoursContainer;
    cv::findContours(input, contoursContainer, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> hullsContainer(contoursContainer.size());

    for(size_t i=0; i<contoursContainer.size(); i++){
        cv::convexHull(contoursContainer[i], hullsContainer[i]);
    }

    //Calculate size of contour


    for(int i=0; i<contoursContainer.size(); i++){
        cv::RotatedRect minRect = cv::minAreaRect(cv::Mat(contoursContainer[i]));

        float h = minRect.size.height;
        float w = minRect.size.width;
        float ratio = h/w;
        float s = w*h;

        if(w > h){
            float t = h;
            h = w;
            w = t;
        }

        // float obHei = PobjectRec.height;
        // float obWid = PobjectRec.width;

        // if (obWid > obHei)
        // {
        //     float t = obHei;
        //     obHei = obWid;
        //     obWid = t;
        // }

        if(h > 100 && w > 100){
            findObjectRectangle(output, contoursContainer[i], color, TextDisplay, objNum);
            visibleCounter += 1;
        }
    }

    obManager->visibleObjectNumber = visibleCounter;
}

void ImageProcessor::findObjectRectangle(cv::Mat &mat, std::vector<cv::Point> contour, cv::Scalar color, QString TextDisplay, int objNum)
{
    //Get object positon from contour
    cv::RotatedRect minRect = cv::minAreaRect(cv::Mat(contour));

    cv::Point2f rectPoints[4];
    minRect.points(rectPoints);

    // Draw a rectangle outside the object
    for (int j = 0; j < 4; j++){
        cv::line(mat, rectPoints[j], rectPoints[(j + 1) % 4], color, 2, 8);
    }

    int xRealObject = 0;
    int yRealObject = 0;

    cv::Mat PPoint = (cv::Mat_<float>(3,1) << minRect.center.x, minRect.center.y, 1);
    /*cv::putText(mat, "[" + std::to_string((int)PPoint.at<float>(0,0)) + ", " + std::to_string((int)PPoint.at<float>(1, 0)) + "]", cv::Point(minRect.center.x + minRect.size.width/2, minRect.center.y - minRect.size.height / 2),
        cv::FONT_HERSHEY_PLAIN, 1, WHITE_COLOR, 2);*/

    cv::Mat RPoint = P2RMatrix * PPoint;

    xRealObject = RPoint.at<float>(0,0);
    yRealObject = RPoint.at<float>(1,0);

    //qDebug() << "x real object" << xRealObject;
    //qDebug() << "y real object" << yRealObject;

    cv::RotatedRect realObject = minRect;

    realObject.center.x = xRealObject;
    realObject.center.y = yRealObject;
    realObject.size.height = minRect.size.height / PnRRatio;
    realObject.size.width = minRect.size.width / PnRRatio;

    obManager->addNewObject(realObject, objNum);


    cv::putText(mat, "[" + std::to_string((int)xRealObject) + ", " + std::to_string((int)yRealObject) + "]", cv::Point(minRect.center.x - 40, minRect.center.y),
                cv::FONT_HERSHEY_PLAIN, 1, WHITE_COLOR, 2);
    cv::putText(mat, TextDisplay.toStdString(), cv::Point(minRect.center.x + minRect.size.width/2, minRect.center.y - minRect.size.height/2),
        cv::FONT_HERSHEY_PLAIN, 2, WHITE_COLOR, 2);
    //qDebug() << "Angle: " << minRect.angle;

}

void ImageProcessor::updateTrackingInfor()
{
    lbTrackingObjectNumber->setText(QString::number(obManager->objectContainer.size()));
    lbVisibleObjectNumber->setText(QString::number(obManager->visibleObjectNumber));
    lbObject1Name->setText(nameObjectInfor[0]);
    lbObject2Name->setText(nameObjectInfor[1]);
    lbObject3Name->setText(nameObjectInfor[2]);
    lbObject1Number->setText(QString::number(obManager->objectNumber1));
    lbObject2Number->setText(QString::number(obManager->objectNumber2));
    lbObject3Number->setText(QString::number(obManager->objectNumber3));
}

void ImageProcessor::updateObjectPositionOnConveyor()
{
    float distance = conveyorSpd * ((float)timerTool.elapsed() / 1000);
    timerTool.restart();

    obManager->updateNewPositionObjects(distance);

    emit objectPositionChanged(obManager->objectContainer);
}

void ImageProcessor::setConveyorSpeed(int vel)
{
    conveyorSpd = vel;
}

void ImageProcessor::makeBrightProcessRegion(cv::Mat resultMats)
{
    cv::Mat filterMat(cv::Size(resultMats.cols, resultMats.rows), CV_8UC1, BLACK_COLOR);


    cv::Rect rect;
    rect.width = PSelectedRect.width;
    rect.height = PSelectedRect.height;
    rect.x = PSelectedRect.x;
    rect.y = PSelectedRect.y;

    cv::rectangle(filterMat, rect, WHITE_COLOR, cv::FILLED);

    int darkValue = 60;

    for (int y = 0; y < resultMats.rows; y++)
    {
        for (int x = 0; x < resultMats.cols; x++)
        {
            for (int c = 0; c < resultMats.channels(); c++)
            {
                int vl = resultMats.at<cv::Vec3b>(y, x)[c] - darkValue;

                if (vl < 0)
                    vl = 0;

                if (filterMat.at<uchar>(y, x) == 0)
                {
                    resultMats.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(vl);
                }
            }
        }
    }

}

void ImageProcessor::selectProcessingRegion(cv::Mat proImg)
{
    cv::Mat filterMat(cv::Size(proImg.cols, proImg.rows), CV_8UC1, BLACK_COLOR);
    cv::rectangle(filterMat, PSelectedRect, WHITE_COLOR, cv::FILLED);
    
    cv::bitwise_and(filterMat, proImg, proImg);
}

void ImageProcessor::drawBlackWhiteLine(cv::Mat displayMat, cv::Point p1, cv::Point p2, int thin)
{
    cv::line(displayMat, p1, p2, BLACK_COLOR, thin);
    cv::line(displayMat, cv::Point(p1.x + 1, p1.y + 1), cv::Point(p2.x + 1, p2.y + 1), WHITE_COLOR, thin);
}

void ImageProcessor::drawBlackWhiteLine(cv::Mat displayMat, QLine line, int thin)
{
    cv::Point p1 = cv::Point(line.x1(), line.y1());
    cv::Point p2 = cv::Point(line.x2(), line.y2());

    drawBlackWhiteLine(displayMat, p1, p2, thin);
}

void ImageProcessor::drawBlackWhiteLines(cv::Mat displayMat, std::vector<cv::Point> points, int thin)
{
    cv::polylines(displayMat, points, true, BLACK_COLOR, thin);
    cv::polylines(displayMat, points, true, WHITE_COLOR, thin);
}

void ImageProcessor::drawBlackWhiteRect(cv::Mat displayMat, cv::Point p, cv::Size size)
{
    cv::rectangle(displayMat, cv::Rect(p, size), BLACK_COLOR, 1);
    cv::rectangle(displayMat, cv::Rect(cv::Point(p.x + 1, p.y + 1), size), WHITE_COLOR, 1);
}

void ImageProcessor::drawBlackWhiteRect(cv::Mat displayMat, cv::Rect rect)
{
    cv::Point pos = cv::Point(rect.x, rect.y);
    cv::Point pos2 = cv::Point(rect.x - 1, rect.y - 1);
    cv::Size size = cv::Size(rect.size().width, rect.size().height);
    cv::Size size2 = cv::Size(rect.size().width + 2, rect.size().height + 2);

    cv::rectangle(displayMat, cv::Rect(pos, size), BLACK_COLOR, 1);
    cv::rectangle(displayMat, cv::Rect(pos2, size2), WHITE_COLOR, 1);
}

void ImageProcessor::drawLine(cv::Mat displayMat, cv::Point p1, cv::Point p2)
{
    drawBlackWhiteLine(displayMat, p1, p2, 1);
}

void ImageProcessor::drawCorner(cv::Mat displayMat, cv::Point p)
{
    cv::Point RectcvPoint1 = cv::Point(p.x - 4, p.y - 4);

    drawBlackWhiteRect(displayMat, RectcvPoint1, cv::Size(10, 10));
}

void ImageProcessor::transformPerspective(cv::Mat inputMat, std::vector<cv::Point> points, cv::Mat outputMat)
{
    cv::Point2f inputQuad[4];
    cv::Point2f outputQuad[4];

    inputQuad[0] = points[0];
    inputQuad[1] = points[1];
    inputQuad[2] = points[2];
    inputQuad[3] = points[3];

    // ----- Find new position -------

    cv::Point2f center;
    center.x = (points[0].x + points[1].x + points[2].x + points[3].x) / 4;
    center.y = (points[0].y + points[1].y + points[2].y + points[3].y) / 4;

    int maxLength = 0;

    for (int i = 0; i < 4; ++i) {
        QLineF line;
        line.setP1(QPoint(inputQuad[i].x, inputQuad[i].y));
        if (i == 3) {
            line.setP2(QPoint(inputQuad[0].x, inputQuad[0].y));
        }
        else {
            line.setP2(QPoint(inputQuad[i+1].x, inputQuad[i+1].y));
        }

        int len = line.length();
        if (len > maxLength) maxLength = len;
    }

    int halfLen = maxLength / 2;

    outputQuad[0] = center + cv::Point2f(-halfLen, -halfLen);
    outputQuad[1] = center + cv::Point2f(-halfLen, halfLen);
    outputQuad[2] = center + cv::Point2f(halfLen, halfLen);
    outputQuad[3] = center + cv::Point2f(halfLen, -halfLen);

    //cv::Mat lambda = cv::Mat::zeros(inputMat.rows, inputMat.cols, inputMat.type());

    cv::Mat lambda = cv::getPerspectiveTransform(inputQuad, outputQuad);

    cv::warpPerspective(inputMat, outputMat, lambda, outputMat.size());
}

void ImageProcessor::updateRatios()
{
    //Tỷ lệ chuyển đổi từ kích thước label screen sang kích thước thực camera
    DnPRatio = (float)lbResultImage->width()/camera->get(cv::CAP_PROP_FRAME_WIDTH);

    DnPWRatio = (float)lbResultImage->width() / camera->get(cv::CAP_PROP_FRAME_WIDTH);
    DnPHRatio = (float)lbResultImage->height() / camera->get(cv::CAP_PROP_FRAME_HEIGHT);

    //qDebug() << "DnPWRatio = " << DnPWRatio;
    //qDebug() << "DnPHRatio = " << DnPHRatio;
    
    cameraRatio = (float)camera->get(cv::CAP_PROP_FRAME_WIDTH)/camera->get(cv::CAP_PROP_FRAME_HEIGHT);
}

void ImageProcessor::saveSetting()
{
    if (imgMode != CALIB) return;
    lbResultImage->saveSetting();
}

void ImageProcessor::loadSetting()
{
    if (imgMode != CALIB) return;
    lbResultImage->loadSetting();
}



