#ifndef PIXEL_H
#define PIXEL_H

#include<opencv2/core/core.hpp>

class Pixel : public cv::Vec<unsigned char,3>
{
public:
    Pixel();
};

#endif // PIXEL_H
