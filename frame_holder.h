#ifndef FRAME_HOLDER_H
#define FRAME_HOLDER_H

#include "video_dispatch.h"
#include <opencv2/core/core.hpp>
#include <atomic>
class FrameHolder : public VideoReceiver
{
public:
    FrameHolder();
    void update(Mat *frame);
    cv::Mat* getLastFrame();
private:
     std::atomic<cv::Mat*> lastFrame;
};

#endif // FRAME_HOLDER_H
