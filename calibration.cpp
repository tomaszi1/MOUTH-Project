#include "calibration.h"
#include <QDebug>
#include <QPoint>
#include <QSize>
#include <opencv2/imgproc/imgproc.hpp>
Calibration::Calibration()
{
    state = OFF;
    lowerHBound = 255;
    lowerVBound = 255;
    lowerSBound = 255;
    higherVBound = 0;
    higherSBound = 0;
    higherHBound = 0;
}

void Calibration::setFrameHolder(FrameHolder *holder){
    frameHolder = holder;
}

void Calibration::setState(CalibrationState state)
{
    this->state = state;
}

void Calibration::receiveClickedPixel(QPoint point, QSize size)
{
    if(state != IN_PROGRESS)
        return;

    cv::Mat* frame = frameHolder->getLastFrame();
    if(frame==NULL)
        return;

    cv::cvtColor(*frame,*frame,CV_BGR2HSV);
    //cv::medianBlur(*frame,*frame,5);
    cv::GaussianBlur(*frame,*frame,cv::Size(5,5),0);
    double xPosCoef = (double)point.x()/size.width();
    double yPosCoef = (double)point.y()/size.height();

    int finalXPos = (int)(xPosCoef*frame->rows);
    int finalYPos = (int)(yPosCoef*frame->cols);
    Vec3b pixel = frame->at<cv::Vec3b>(finalXPos,finalYPos);
    qDebug() << "H:" << pixel[0] << " S:" << pixel[1] << " V:" << pixel[2];

    if(pixel[0]>higherHBound)
        higherHBound=pixel[0];
    if(pixel[0]<lowerHBound)
        lowerHBound=pixel[0];
    if(pixel[1]>higherSBound)
        higherSBound=pixel[1];
    if(pixel[1]<lowerSBound)
        lowerSBound=pixel[1];
    if(pixel[2]>higherVBound)
        higherVBound=pixel[2];
    if(pixel[2]<lowerVBound)
        lowerVBound=pixel[2];


    cv::Mat thresh;
    cv::inRange(*frame,Scalar(lowerHBound,lowerSBound,lowerVBound),Scalar(higherHBound,higherSBound,higherVBound),thresh);

    cv::imshow("debug",thresh);
    cv::imshow("img",*frame);

    qDebug()<<"R:"<<lowerHBound<<","<<lowerHBound;
    qDebug()<<"R:"<<lowerSBound<<","<<lowerSBound;
    qDebug()<<"R:"<<lowerVBound<<","<<lowerVBound;

}
