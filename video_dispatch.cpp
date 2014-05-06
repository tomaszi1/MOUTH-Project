#include "video_dispatch.h"
#include <vector>
#include <algorithm>
#include <opencv2/core/core.hpp>

VideoDispatcher::VideoDispatcher(Camera *camera){
    this->camera = camera;
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

    for(unsigned int i=0;i<observers.size();i++)
        observers[i]->update();
}
