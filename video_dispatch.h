#ifndef VIDEO_DISPATCH_H
#define VIDEO_DISPATCH_H

#include<vector>
#include<QObject>
#include "camera.h"

class VideoReceiver;

class VideoDispatcher : public QObject
{
    Q_OBJECT
public:
    VideoDispatcher();
    ~VideoDispatcher();
    void attach(VideoReceiver* obs);
    void remove(VideoReceiver* obs);
public slots:
    void dispatchFrame();
private:
    std::vector<class VideoReceiver*> observers;
    Camera *camera;
};

class VideoReceiver{
public:
    virtual void update(Mat* frame) = 0;
};

#endif
