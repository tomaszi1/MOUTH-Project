#include "maskoverlay.h"
#include<opencv2/core/core.hpp>
MaskOverlay::MaskOverlay()
{
    mask=NULL;
}

void MaskOverlay::setMask(cv::Mat &mask){
    this->mask = &mask;
}

void MaskOverlay::process(cv::Mat &image)
{
    if(mask==NULL)
        return;


}
