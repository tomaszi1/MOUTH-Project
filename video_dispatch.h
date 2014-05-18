#ifndef VIDEO_DISPATCH_H
#define VIDEO_DISPATCH_H

#include<vector>
#include<QObject>
#include "camera.h"
#include<QMutex>
#include<QThread>
#include "imageprocessor.h"
class VideoReceiver;

class VideoDispatcher : public QObject
{
    Q_OBJECT
public:
    VideoDispatcher();
    ~VideoDispatcher();
    void attach(VideoReceiver* obs);
    void remove(VideoReceiver* obs);
    void removeAll();
    void setPreprocessor(ImageProcessor&);
public slots:
    void dispatchFrame();
private:
    std::vector<class VideoReceiver*> observers;
    Camera *camera;
    QMutex dispatchGuard;
    ImageProcessor *preprocessor;
};

class VideoReceiver{
public:
    virtual void update(Mat* frame) = 0;
};

class DispatcherThread : public QThread{

};

#endif
