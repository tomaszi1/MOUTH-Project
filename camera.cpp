#include "camera.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Camera::Camera()
{
    currectCameraIndex = 0;
    currentCamera.open(0);
    if(!currentCamera.isOpened())
        throw "No camera detected!";
}

Mat* Camera::read(){
    Mat* image = new cv::Mat();
    currentCamera.read(*image);
    return image;
}

bool Camera::switchCamera(){
    currentCamera.release();
    currectCameraIndex++;
    currentCamera.open(currectCameraIndex);
    if(!currentCamera.isOpened()){
        currentCamera.open(0);
        currectCameraIndex = 0;
    }
    return currentCamera.isOpened();
}

bool Camera::isOpened(){
    return currentCamera.isOpened();
}

void Camera::close(){
    currentCamera.release();
}

Camera* Camera::getInstance(){
    static Camera instance;
    return &instance;
}

double Camera::getHeight(){
    return currentCamera.get(CV_CAP_PROP_FRAME_HEIGHT);
}

double Camera::getWidth(){
    return currentCamera.get(CV_CAP_PROP_FRAME_WIDTH);
}
