#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Camera
{
public:
    static Camera* getInstance();
    Mat* read();
    bool switchCamera();
    bool isOpened();
    void close();
    double getWidth();
    double getHeight();

private:
    Camera();
    VideoCapture currentCamera;
    int currectCameraIndex;

};

#endif // CAMERA_H
