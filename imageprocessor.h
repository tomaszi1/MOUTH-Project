#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include <opencv2/core/core.hpp>
class ImageProcessor
{
public:
    virtual void process(cv::Mat& image) = 0;
};

#endif // IMAGEPROCESSOR_H
