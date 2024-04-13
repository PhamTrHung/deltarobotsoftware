#include "objectmanager.h"
#include <QDebug>

ObjectManager::ObjectManager(QObject *parent)
    : QObject{parent}
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::addNewObject(cv::RotatedRect object)
{
    if(isNewObject(object)){
        objectContainer.push_back(object);
    }
}

void ObjectManager::updateNewPositionObjects(float deltaX, float deltaY)
{

}

void ObjectManager::removeOldestObjects()
{

}

void ObjectManager::removeAllDetectObjects()
{
    objectContainer.clear();
}

bool ObjectManager::isNewObject(cv::RotatedRect object)
{
    for(int i=0; i<objectContainer.size(); i++){
        cv::RotatedRect oldObj = objectContainer[i];

        std::vector<cv::Point2f> intersectionVertices;

        //Output: intersectionVertices -> So canh giao nhau giua 2  rotated Rectangle
        cv::rotatedRectangleIntersection(oldObj, object, intersectionVertices);

        int intersectionArea = 0;

        //Neu so canh giao nhau > 0, tinh dien tich vung giao nhau
        if(intersectionVertices.size() > 0){
            intersectionArea = cv::contourArea(intersectionVertices);
        }

        //Tính diện tích đối tượng cũ
        int objectArea = oldObj.size.height * oldObj.size.width;

        //Nếu diện tích vùng giao nhau lớn hơn diện tích đối tượng cũ 30% thì 2 đối tượng trùng nhau
        if(intersectionArea > objectArea * 0.3f){
            objectContainer[i].center.x = object.center.x;
            objectContainer[i].center.y = object.center.y;
            return false;
        }
    }
    return true;
}
