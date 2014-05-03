#include "camera.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Camera::Camera()
{
    currentCamera.open(0);
    if(currentCamera.isOpened())
        throw "Kamera niedostepna!";
}

Mat* Camera::read(){
    Mat* image = new cv::Mat();
    currentCamera.read(image);
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
}

bool Camera::isOpened(){
    return currentCamera.isOpened();
}

void Camera::close(){
    currentCamera.release();
}
