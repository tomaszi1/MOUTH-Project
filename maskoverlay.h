#ifndef MASKOVERLAY_H
#define MASKOVERLAY_H
#include "imageprocessor.h"
#include <opencv2/core/core.hpp>
class MaskOverlay : public ImageProcessor
{
public:
    MaskOverlay();
    void setMask(cv::Mat &mask);
    void process(cv::Mat &image);

private:
    cv::Mat* mask;
};

#endif // MASKOVERLAY_H
