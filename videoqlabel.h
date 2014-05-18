#ifndef VIDEOQLABEL_H
#define VIDEOQLABEL_H
#include "video_dispatch.h"
#include "imageprocessor.h"
#include<QLabel>
#include<QMouseEvent>
#include<QPoint>
#include<QSize>
#include<QMutex>
#include<opencv2/core/core.hpp>

class VideoQLabel : public QLabel, public VideoReceiver
{
    Q_OBJECT
signals:
    void mousePressed(const QPoint pos,const QSize size);
    void mouseMoved(const QPoint pos, const QSize size);
public:
    VideoQLabel(QWidget *parent);
    void setActiveClick(bool value);
    bool isActiveClick();
    void update(Mat *frame);
private:
    bool activeClick;
    QMutex updateGuard;
    cv::Mat* currentFrame;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // VIDEOQLABEL_H
