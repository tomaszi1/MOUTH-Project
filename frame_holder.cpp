#include "frame_holder.h"
#include<opencv2/core/core.hpp>
#include <atomic>
FrameHolder::FrameHolder(){
    lastFrame.store(NULL);
}

void FrameHolder::update(cv::Mat *frame){
    cv::Mat* prevFrame;
    prevFrame = lastFrame.exchange(frame);
    delete prevFrame;
}

cv::Mat* FrameHolder::getLastFrame(){
    return lastFrame.exchange(NULL);
}
