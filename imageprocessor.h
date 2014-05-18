#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include <opencv2/core/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
class ImageProcessor
{
public:
    virtual void process(cv::Mat& image) = 0;
};

class Bgr2Rgb : public ImageProcessor
{
public:
    Bgr2Rgb();
    void process(cv::Mat& image);
};

class MouthClassifierProcessor : public ImageProcessor
{
public:
    MouthClassifierProcessor(cv::CascadeClassifier &face,cv::CascadeClassifier &mouth);
    void process(cv::Mat &image);

private:
    cv::CascadeClassifier *mouthClassifier;
    cv::CascadeClassifier *faceClassifier;
};

#endif // IMAGEPROCESSOR_H
