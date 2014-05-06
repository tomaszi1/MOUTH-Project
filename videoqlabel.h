#ifndef VIDEOQLABEL_H
#define VIDEOQLABEL_H
#include "video_dispatch.h"
#include<QLabel>

class VideoQLabel : public QLabel, public VideoReceiver
{
public:
    VideoQLabel(QWidget *parent);
private:

    // methods
    void update(Mat *frame);
};

#endif // VIDEOQLABEL_H
