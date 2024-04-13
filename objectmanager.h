#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = nullptr);
    ~ObjectManager();

    void addNewObject(cv::RotatedRect object);

    int visibleObjectNumber = 0;
    std::vector<cv::RotatedRect> objectContainer;

public slots:
    void updateNewPositionObjects(float deltaX, float deltaY);
    void removeOldestObjects();
    void removeAllDetectObjects();

signals:
    void newUpdateObjectPositon(QString name, float value);

private:
    bool isNewObject(cv::RotatedRect object);
    cv::Point3i approValue;
};

#endif // OBJECTMANAGER_H
