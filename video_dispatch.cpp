#include "video_dispatch.h"
#include <vector>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

VideoDispatcher::VideoDispatcher(){
    camera = Camera::getInstance();
}

VideoDispatcher::~VideoDispatcher(){
    camera->close();
}

void VideoDispatcher::attach(VideoReceiver *obs){
    observers.push_back(obs);
}

void VideoDispatcher::remove(VideoReceiver *obs){
    observers.erase(std::remove(observers.begin(),observers.end(),obs),observers.end());
}

void VideoDispatcher::dispatchFrame(){
    if(observers.empty())
        return;

    cv::Mat* frame = camera->read();
    if(frame==NULL || frame->empty())
        return;

    cv::Mat* copy;
    for(unsigned int i=0;i<observers.size();i++){
        copy = new Mat(*frame);
        observers[i]->update(copy);
    }
    delete frame;
}
