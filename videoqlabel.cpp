#include "videoqlabel.h"
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <opencv2/imgproc/imgproc.hpp>
VideoQLabel::VideoQLabel(QWidget *parent) : QLabel(parent)
{
    activeClick = false;
}

void VideoQLabel::update(Mat *frame){
    if(frame==NULL || frame->empty())
        return;
    cv::cvtColor(*frame,*frame,CV_BGR2RGB);
    cv::GaussianBlur(*frame,*frame,cv::Size(5,5),0);
    //cv::medianBlur(*frame,*frame,5);
    QImage qimage((uchar*)(*frame).data,(*frame).cols,(*frame).rows,(*frame).step,QImage::Format_RGB888);
    if(qimage.size()!=this->size())
        qimage = qimage.scaled(this->size());
    setPixmap(QPixmap::fromImage(qimage));
    delete frame;
}

void VideoQLabel::mousePressEvent(QMouseEvent *event){
    if(!activeClick)
        return;
    const QPoint pos = event->pos();
    const QSize size = this->size();
    qDebug() << pos << " " << size;
    emit mousePressed(pos,size);
}

void VideoQLabel::setActiveClick(bool value){
    activeClick = value;
}

bool VideoQLabel::isActiveClick(){
    return activeClick;
}
