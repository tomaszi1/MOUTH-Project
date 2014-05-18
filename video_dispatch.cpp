#include "video_dispatch.h"
#include <vector>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

VideoDispatcher::VideoDispatcher(){
    camera = Camera::getInstance();
    preprocessor=NULL;
}

VideoDispatcher::~VideoDispatcher(){
    camera->close();
}

void VideoDispatcher::attach(VideoReceiver *obs){
    dispatchGuard.lock();
    observers.push_back(obs);
    dispatchGuard.unlock();
}

void VideoDispatcher::remove(VideoReceiver *obs){
    dispatchGuard.lock();
    observers.erase(std::remove(observers.begin(),observers.end(),obs),observers.end());
    dispatchGuard.unlock();
}

void VideoDispatcher::removeAll()
{
    dispatchGuard.lock();
    observers.clear();
    dispatchGuard.unlock();
}

void VideoDispatcher::setPreprocessor(ImageProcessor &preproc)
{
    dispatchGuard.lock();
    preprocessor = &preproc;
    dispatchGuard.unlock();
}

void VideoDispatcher::dispatchFrame(){
    dispatchGuard.lock();
    cv::Mat* frame;
    if(observers.empty()){
        goto finalize;
    }
    frame = camera->read();
    if(frame==NULL){
        goto finalize;
    }else if(frame->empty()){
        delete frame;
        goto finalize;
    }

    if(preprocessor!=NULL)
        preprocessor->process(*frame);

    cv::Mat* copy;
    for(unsigned int i=0;i<observers.size();i++){
        copy = new Mat(*frame);
        observers[i]->update(copy);
    }
    delete frame;
    finalize:
    dispatchGuard.unlock();
}
