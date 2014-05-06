#include "videoqlabel.h"
#include <QLabel>
#include <QPixmap>
VideoQLabel::VideoQLabel(QWidget *parent) : QLabel(parent)
{
}

void VideoQLabel::update(Mat *frame){
    if(frame==NULL || frame->empty())
        return;
    QImage qimage((uchar*)(*frame).data,(*frame).cols,(*frame).rows,(*frame).step,QImage::Format_RGB888);
    setPixmap(QPixmap::fromImage(qimage));
}
