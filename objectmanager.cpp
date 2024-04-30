#include "objectmanager.h"
#include <QDebug>

ObjectManager::ObjectManager(QObject *parent)
    : QObject{parent}
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::addNewObject(cv::RotatedRect object, int objNum)
{
    if(isNewObject(object)){
        objectContainer.push_back(object);
        object_type.push_back(objNum + 1);
        if (objNum + 1 == 1) {
            objectNumber1++;
        }
        else if (objNum + 1 == 2) {
            objectNumber2++;
        }
        else if (objNum + 1 == 3) {
            objectNumber3++;
        }
    }
}

void ObjectManager::updateNewPositionObjects(float deltaY)
{
    if (objectContainer.size() == 0) return;

    for (int i = 0; i < objectContainer.size(); ++i) {
        objectContainer.at(i).center.y += deltaY;
    }

    for (int i = 0; i < objectContainer.size(); ++i) {
        emit newUpdateObjectPositon(QString("#O%1_X").arg(i + 1), objectContainer.at(i).center.x);
        emit newUpdateObjectPositon(QString("#O%1_Y").arg(i + 1), objectContainer.at(i).center.y);
        emit newUpdateObjectPositon(QString("#O%1_T").arg(i + 1), object_type[i]);
    }
}

void ObjectManager::removeOldestObjects()
{
    if (objectContainer.size() == 0) return;

    for (int i = 0; i < objectContainer.size() - 1; ++i) {
        emit newUpdateObjectPositon(QString("#O%1_X").arg(i + 1), objectContainer.at(i+1).center.x);
        emit newUpdateObjectPositon(QString("#O%1_Y").arg(i + 1), objectContainer.at(i+1).center.y);
        emit newUpdateObjectPositon(QString("#O%1_T").arg(i + 1), object_type[i+1]);
    }

    //Truong hop size = 1
    emit newUpdateObjectPositon(QString("#O%1_X").arg(objectContainer.size()), NULL_NUMBER);
    emit newUpdateObjectPositon(QString("#O%1_Y").arg(objectContainer.size()), NULL_NUMBER);
    emit newUpdateObjectPositon(QString("#O%1_T").arg(object_type.size()), 0);

    objectContainer.erase(objectContainer.begin());
    object_type.erase(object_type.begin());
}

void ObjectManager::removeAllDetectObjects()
{

    for (int i = 0; i < objectContainer.size(); ++i) {
        emit newUpdateObjectPositon(QString("#O%1_X").arg(i + 1), NULL_NUMBER);
        emit newUpdateObjectPositon(QString("#O%1_Y").arg(i + 1), NULL_NUMBER);
        emit newUpdateObjectPositon(QString("#O%1_T").arg(i + 1), 0);
    }

    objectContainer.clear();
    objectNumber1 = 0;
    objectNumber2 = 0;
    objectNumber3 = 0;
    object_type.clear();
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
        int oldObjectArea = oldObj.size.height * oldObj.size.width;

        //Nếu diện tích vùng giao nhau lớn hơn diện tích đối tượng cũ 30% thì 2 đối tượng trùng nhau
        if(intersectionArea > oldObjectArea * 0.3f){
            objectContainer[i].center.x = object.center.x;
            objectContainer[i].center.y = object.center.y;
            return false;
        }
    }
    return true;
}
