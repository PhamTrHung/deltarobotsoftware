#include "imageprocessor.h"
#include <QDebug>


ImageProcessor::ImageProcessor(QWidget *parent)
    :QWidget(parent)
{
    //mParent = parent;

    parameterPanel = new HSVWindow(parent);
    connect(parameterPanel, SIGNAL(valueChanged(int,int,int,int,int,int)),
            this, SLOT(setHSV(int,int,int,int,int,int)));

    camera = new cv::VideoCapture();

    updateScreenTimer = new QTimer(this);
    connect(updateScreenTimer, SIGNAL(timeout()), this, SLOT(updateCameraScreen()));
    updateScreenTimer->start(cameraTimerInterval);

    obManager = new ObjectManager(parent);

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
    //label->setScaledContents(true);
    //label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void ImageProcessor::setImageScreen(CameraWidget *screen)
{
    lbResultImage = screen;
}

void ImageProcessor::setObjectInforLabelWidget(QLabel *lbTracking, QLabel *lbVisible)
{
    lbTrackingObjectNumber = lbTracking;
    lbVisibleObjectNumber = lbVisible;
}

void ImageProcessor::setMeasureParameterPointer(QLineEdit *xCoor, QLineEdit *yCoor, QLineEdit *distance)
{
    leDistance = distance;
    leXCoor = xCoor;
    leYCoor = yCoor;
}

void ImageProcessor::displayAdditionalInfor()
{
    if (calibImage.empty()) return;
    cv::putText(calibImage, std::string("x = ") + leXCoor->text().toStdString() + ", y = " + leYCoor->text().toStdString(), cv::Point(DCalibPoint.x(), DCalibPoint.y() + 15), cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255, 255, 0), 1);
    cv::putText(calibImage, leDistance->text().toStdString() + " mm", cv::Point(DCalibLine.center().x() - 15, DCalibLine.center().y() + 15), cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255, 255, 0), 1);
}

void ImageProcessor::loadCamera(bool state)
{
    if(state){

        if(cameraFPS >= 15 && cameraFPS <= 30){
            updateScreenTimer->stop();
            cameraTimerInterval = 1000/cameraFPS;
            updateScreenTimer->start(cameraTimerInterval);
        }

        camera->open(idCamera, cv::CAP_DSHOW);
        camera->set(cv::CAP_PROP_FRAME_WIDTH, 600);
        camera->set(cv::CAP_PROP_FRAME_HEIGHT, 400);

        lbResultImage->initParameter();
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

    //updateLabelImage(captureImage, lbResultImage);
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

void ImageProcessor::getCalibPoint(int x, int y)
{
    DCalibPoint.setX(x);
    DCalibPoint.setY(y);

    if (captureImage.cols > 0) {
        PcalibPoint.x = x / DnPRatio;
        PcalibPoint.y = y / DnPRatio;
    }

    if (leXCoor == nullptr) return;

    float xRealCalibPoint = leXCoor->text().toFloat();
    float yRealCalibPoint = leYCoor->text().toFloat();

    // X axis up
    float theta = M_PI_2;

    cv::Mat rotateMatrix = (cv::Mat_<float>(3, 3) << cos(theta), -sin(theta), 0,
                                                     sin(theta), cos(theta), 0,
                                                     0, 0, 1);

    cv::Mat scaleMatrix = (cv::Mat_<float>(3, 3) << 1.0f / PnRRatio, 0, 0,
                                                    0, 1.0f / PnRRatio, 0,
                                                    0, 0, 1);
    
    cv::Mat scaleRotateMatrix = rotateMatrix * scaleMatrix;

    // x' = m11 * x + m21 * y + dx   --> dx = x' - (m11 * x + m21 * y)
    // y' = m12 * x + m22 * y + dy   --> dy = y' - (m12 * x + m22 * y)

    float dx = xRealCalibPoint - (scaleRotateMatrix.at<float>(0, 0) * (x / DnPRatio) + scaleRotateMatrix.at<float>(1, 0) * (y / DnPRatio));
    float dy = yRealCalibPoint - (scaleRotateMatrix.at<float>(0, 1) * (x / DnPRatio) + scaleRotateMatrix.at<float>(1, 1) * (y / DnPRatio));

    P2RMatrix = (cv::Mat_<float>(3, 3) << scaleRotateMatrix.at<float>(0, 0), scaleRotateMatrix.at<float>(0, 1), 0,
                                          scaleRotateMatrix.at<float>(1, 0), scaleRotateMatrix.at<float>(1, 1), 0,
                                          dx, dy, 1);

    cv::Mat result = P2RMatrix * (cv::Mat_<float>(3, 1) << x / DnPRatio, y / DnPRatio, 0);
    qDebug() << result.at<float>(0, 0);
    qDebug() << result.at<float>(1, 0);
    qDebug() << result.at<float>(2, 0);
}

void ImageProcessor::getDistance(int distance)
{
    float realDistance = leDistance->text().toFloat();

    float processDistance = realDistance / DnPRatio;

    PnRRatio = processDistance / realDistance;
    DnRRatio = (float)distance / realDistance;
}

void ImageProcessor::getProcessArea(QRect processArea)
{
    DSelectedRect = processArea;

    PSelectedRect.width = processArea.width() / DnPRatio;
    PSelectedRect.height = processArea.height() / DnPRatio;
    PSelectedRect.x = processArea.x() / DnPRatio;
    PSelectedRect.y = processArea.y() / DnPRatio;

}

void ImageProcessor::getCalibLine(QPoint p1, QPoint p2)
{
    DCalibLine.setP1(p1);
    DCalibLine.setP2(p2);
}

void ImageProcessor::processImage()
{
    if(!captureImage.data){
        return;
    }

    //Copy to calib image
    captureImage.copyTo(calibImage);

    //Filter image
    HSV_CaptureImage = captureImage.clone();
    cv::cvtColor(HSV_CaptureImage, HSV_CaptureImage, cv::COLOR_BGR2HSV);

    cv::Scalar minScalar(HSV_Value[0], HSV_Value[2], HSV_Value[4]);
    cv::Scalar maxScalar( HSV_Value[1],HSV_Value[3],HSV_Value[5]);

    cv::inRange(HSV_CaptureImage, minScalar, maxScalar, HSV_CaptureImage);

    selectProcessingRegion(HSV_CaptureImage);

    //detect objects in image
    captureImage.copyTo(resultImage);
    detectObject(HSV_CaptureImage, resultImage, BLUE_COLOR);

    //Update object tracking infor
    updateTrackingInfor();

    //display

    if(imgMode == ORIGIN){
        updateLabelImage(captureImage, lbResultImage);
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

void ImageProcessor::detectObject(cv::Mat input, cv::Mat output, cv::Scalar color)
{

    //Find contour in image
    std::vector<std::vector<cv::Point>> contoursContainer;
    cv::findContours(input, contoursContainer, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> hullsContainer(contoursContainer.size());

    for(size_t i=0; i<contoursContainer.size(); i++){
        cv::convexHull(contoursContainer[i], hullsContainer[i]);
    }

    //Calculate size of contour

    int visibleCounter = 0;

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

        if(h > 30 && w > 30){
            findObjectRectangle(output, contoursContainer[i], color);
            visibleCounter += 1;
        }
    }

    obManager->visibleObjectNumber = visibleCounter;
}

void ImageProcessor::findObjectRectangle(cv::Mat &mat, std::vector<cv::Point> contour, cv::Scalar color)
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

    cv::Mat PPoint = (cv::Mat_<float>(3,1) << minRect.center.x / DnPRatio, minRect.center.y / DnPRatio, 0);
    cv::Mat RPoint = P2RMatrix * PPoint;

    xRealObject = RPoint.at<float>(0,0);
    yRealObject = RPoint.at<float>(1,0);

    cv::RotatedRect realObject = minRect;

    realObject.center.x = xRealObject;
    realObject.center.y = yRealObject;
    realObject.size.height = minRect.size.height / PnRRatio;
    realObject.size.width = minRect.size.width / PnRRatio;

    obManager->addNewObject(realObject);


    cv::putText(mat, "[" + std::to_string((int)xRealObject) + ", " + std::to_string((int)yRealObject) + "]", cv::Point(minRect.center.x - 40, minRect.center.y),
                cv::FONT_HERSHEY_PLAIN, 1, WHITE_COLOR, 2);

}

void ImageProcessor::updateTrackingInfor()
{
    lbTrackingObjectNumber->setText(QString::number(obManager->objectContainer.size()));
    lbVisibleObjectNumber->setText(QString::number(obManager->visibleObjectNumber));
}

void ImageProcessor::updateObjectPositionOnConveyor()
{
    emit objectPositionChanged(obManager->objectContainer);
}

void ImageProcessor::makeBrightProcessRegion(cv::Mat resultMats)
{
    cv::Mat filterMat(cv::Size(resultMats.cols, resultMats.rows), CV_8UC1, BLACK_COLOR);


    cv::Rect rect;
    rect.width = DSelectedRect.width();
    rect.height = DSelectedRect.height();
    rect.x = DSelectedRect.x();
    rect.y = DSelectedRect.y() + 30;

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

void ImageProcessor::updateRatios()
{
    //Tỷ lệ chuyển đổi từ kích thước label screen sang kích thước thực camera
    DnPRatio = (float)lbResultImage->width()/camera->get(cv::CAP_PROP_FRAME_WIDTH);
    
    cameraRatio = (float)camera->get(cv::CAP_PROP_FRAME_WIDTH)/camera->get(cv::CAP_PROP_FRAME_HEIGHT);

}

