#include "videoqlabel.h"
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <opencv2/imgproc/imgproc.hpp>
#include <QPainter>
VideoQLabel::VideoQLabel(QWidget *parent) : QLabel(parent)
{
    activeClick = false;
    connect(this,SIGNAL(updateGuiSignal()),this,SLOT(updateGuiSlot()));
    setScaledContents(true);
    setMouseTracking(true);
}

void VideoQLabel::update(Mat *frame){
    if(frame==NULL || frame->empty())
        return;
    QImage qimage((uchar*)(*frame).data,(*frame).cols,(*frame).rows,(*frame).step,QImage::Format_RGB888);
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

void VideoQLabel::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();
    const QSize size = this->size();
    qDebug() << pos << " " << size;
    emit mouseMoved(pos,size);
}

void VideoQLabel::setActiveClick(bool value){
    activeClick = value;
}

bool VideoQLabel::isActiveClick(){
    return activeClick;
}
