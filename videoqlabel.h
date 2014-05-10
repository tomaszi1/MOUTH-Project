#ifndef VIDEOQLABEL_H
#define VIDEOQLABEL_H
#include "video_dispatch.h"
#include<QLabel>
#include<QMouseEvent>
#include<QPoint>
#include<QSize>
#include<opencv2/core/core.hpp>
class VideoQLabel : public QLabel, public VideoReceiver
{
    Q_OBJECT
signals:
    void mousePressed(const QPoint& pos,const QSize& size);
public:
    VideoQLabel(QWidget *parent);
    void setActiveClick(bool value);
    bool isActiveClick();

private:
    bool activeClick;

    void update(Mat *frame);
    void mousePressEvent(QMouseEvent *event);

};

#endif // VIDEOQLABEL_H
