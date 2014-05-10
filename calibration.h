#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <vector>
#include <QPoint>
#include <QSize>
#include <QObject>
#include "frame_holder.h"
#include "pixel.h"

enum CalibrationState{
    OFF, GATHERING
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
    FrameHolder *frameHolder;
};



#endif // CALIBRATION_H
