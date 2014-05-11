#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <vector>
#include <QPoint>
#include <QSize>
#include <QObject>
#include "frame_holder.h"
#include "pixel.h"

enum CalibrationState{
    OFF, IN_PROGRESS, DONE
};

class Calibration : public QObject
{
    Q_OBJECT
public:
    Calibration();
    void setFrameHolder(FrameHolder*);
    void setState(CalibrationState);
public slots:
    void receiveClickedPixel(QPoint,QSize);
private:
    CalibrationState state;
    std::vector<Pixel> clickedPixels;
    uchar lowerVBound;
    uchar higherVBound;
    uchar lowerSBound;
    uchar higherSBound;
    uchar lowerHBound;
    uchar higherHBound;
    FrameHolder *frameHolder;
};



#endif // CALIBRATION_H
