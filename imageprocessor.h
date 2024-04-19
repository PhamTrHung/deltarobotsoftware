#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QPushButton>
#include <QTimer>
#include <QLineEdit>
#include <qgenericmatrix.h>


#include "camerawidget.h"
#include "hsvwindow.h"
#include "objectmanager.h"

#define RED_COLOR       cv::Scalar(0, 0, 255)
#define GREEN_COLOR     cv::Scalar(0, 255, 0)
#define BLUE_COLOR      cv::Scalar(255, 0, 0)
#define YELLOW_COLOR    cv::Scalar(0, 255, 255)
#define BLACK_COLOR    cv::Scalar(0, 0, 0)
#define WHITE_COLOR    cv::Scalar(255, 255, 255)

#define DEFAULT_FPS 15 //15 khung hinh tren giay
#define DEFAULT_INTERVAL 1000/DEFAULT_FPS

class MainWindow;


class ImageProcessor : public QWidget
{
    Q_OBJECT
public:
    ImageProcessor(QWidget* parent);
    ~ImageProcessor();

    QImage convertMatToImg(cv::Mat mat);
    void updateLabelImage(cv::Mat mat, QLabel *label);
    void loadCamera(bool state);
    void setImageScreen(CameraWidget* screen);

    ObjectManager *obManager;
    void setObjectInforLabelWidget(QLabel* lbTracking, QLabel* lbVisible);
    
    void setMeasureParameterPointer(QLineEdit* xCoor, QLineEdit* yCoor, QLineEdit* distance);

    void displayAdditionalInfor();

    int runningCamera = -1;
    bool isCameraPause = false;
    int idCamera = 0;

    cv::VideoCapture *camera;
    int cameraFPS = DEFAULT_FPS;
    int cameraTimerInterval = DEFAULT_INTERVAL;
    int imageCapturedNumber = 0;

    enum DISPLAY_MODE{
        ORIGIN,
        HSV_PROCESSEING,
        RESULT,
        CALIB,
    };
    DISPLAY_MODE imgMode = ORIGIN;

public slots:

    void updateCameraScreen();
    void captureCamera();
    void saveImage();
    void openParameterPanel(bool);

    void setHSV(int minH, int maxH, int minS, int maxS, int minV, int maxV);

    void getCalibPoint(int, int);
    void getDistance(int);
    void getProcessArea(QRect);
    void getCalibLine(QPoint, QPoint);
    void getPerspectivePoints(QPoint, QPoint, QPoint, QPoint);
    void turnOnPerspectiveMode();
    void turnOffPerspectiveMode();

    void updateRatios();

    void saveSetting();
    void loadSetting();

signals:
    void objectPositionChanged(std::vector<cv::RotatedRect> objectContainer);

private:
    void processImage();
    void detectObject(cv::Mat input, cv::Mat output, cv::Scalar color);
    void findObjectRectangle(cv::Mat &mat, std::vector<cv::Point> contour, cv::Scalar color);

    void updateTrackingInfor();
    void updateObjectPositionOnConveyor();

    void makeBrightProcessRegion(cv::Mat resultMats);
    void selectProcessingRegion(cv::Mat proImg);

    void drawBlackWhiteLine(cv::Mat displayMat, cv::Point p1, cv::Point p2, int thin);
    void drawBlackWhiteLine(cv::Mat displayMat, QLine line, int thin);
    void drawBlackWhiteLines(cv::Mat displayMat, std::vector<cv::Point> points, int thin);
    void drawBlackWhiteRect(cv::Mat displayMat, cv::Point p, cv::Size s);
    void drawBlackWhiteRect(cv::Mat displayMat, cv::Rect rect);
    void drawLine(cv::Mat displayMat, cv::Point p1, cv::Point p2);
    void drawCorner(cv::Mat displayMat, cv::Point p);

    void transformPerspective(cv::Mat inputMat, std::vector<cv::Point> points, cv::Mat outputMat);

    QTimer* updateScreenTimer;
    cv::Mat captureImage;
    cv::Mat HSV_CaptureImage;
    cv::Mat resultImage;
    cv::Mat calibImage;
    cv::Mat originalImage;

    CameraWidget* lbResultImage;

    MainWindow* mParent;

    HSVWindow* parameterPanel;
    int HSV_Value[6] = {0, 100, 0, 255, 0, 255};

    QLabel* lbTrackingObjectNumber;
    QLabel* lbVisibleObjectNumber;

    QLineEdit* leDistance = nullptr;
    QLineEdit* leXCoor = nullptr;
    QLineEdit* leYCoor = nullptr;


    float DnPRatio{ 1.0f };
    float PnRRatio{ 1.0f };
    float DnRRatio{ 1.0f };
    float cameraRatio{ 1.0f };
    
    float DnPWRatio{ 1.0f };
    float DnPHRatio{ 1.0f };

    QPoint DCalibPoint;
    QLine DCalibLine;
    QRect DSelectedRect;
    QPoint DPerspectivePoints[4];
    
    std::vector<cv::Point> PPerspectivePoints;
    cv::Point PcalibPoint;
    cv::Rect PSelectedRect;
    cv::Mat P2RMatrix;

    bool isPerspectiveMode = false;
    float processDistanceValue = 0;
};

#endif // IMAGEPROCESSOR_H
