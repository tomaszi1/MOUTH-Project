#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Camera
{
public:
    Camera();
    Mat* read();
    bool switchCamera();
    bool isOpened();
    void close();

private:
    VideoCapture currentCamera;
    int currectCameraIndex;

};

#endif // CAMERA_MANAGER_H
