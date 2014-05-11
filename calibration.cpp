#include "calibration.h"
#include <QDebug>
#include <QPoint>
#include <QSize>
Calibration::Calibration()
{
    state = OFF;
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
    qDebug() << "receiveClickedPixel";
    if(state != GATHERING)
        return;

    cv::Mat* frame = frameHolder->getLastFrame();
    if(frame==NULL)
        return;

    double xPosCoef = (double)point.x()/size.width();
    double yPosCoef = (double)point.y()/size.height();

    qDebug() << xPosCoef << " " << yPosCoef;

    int finalXPos = (int)(xPosCoef*frame->rows);
    int finalYPos = (int)(yPosCoef*frame->cols);
    Vec3b pixel = frame->at<cv::Vec3b>(finalXPos,finalYPos);
    qDebug() << (uchar)pixel[0] << " " << (uchar)pixel[1] << " " << (uchar)pixel[2];
}
