#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#define NULL_NUMBER -6789

class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = nullptr);
    ~ObjectManager();

    void addNewObject(cv::RotatedRect object, int objNum);

    int visibleObjectNumber = 0;
    std::vector<cv::RotatedRect> objectContainer;
    int objectNumber1{ 0 };
    int objectNumber2{ 0 };
    int objectNumber3{ 0 };

public slots:
    void updateNewPositionObjects(float deltaY);
    void removeOldestObjects();
    void removeAllDetectObjects();

signals:
    void newUpdateObjectPositon(QString name, float value);

private:
    bool isNewObject(cv::RotatedRect object);
    cv::Point3i approValue;
    std::vector<int> object_type;
};

#endif // OBJECTMANAGER_H
