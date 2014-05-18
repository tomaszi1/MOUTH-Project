#include "imageprocessor.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<vector>
using namespace cv;
using namespace std;
Bgr2Rgb::Bgr2Rgb()
{}

void Bgr2Rgb::process(cv::Mat &image)
{
    cvtColor(image,image,CV_BGR2RGB);
}

MouthClassifierProcessor::MouthClassifierProcessor(CascadeClassifier &face, CascadeClassifier &mouth)
{
    this->mouthClassifier = &mouth;
    this->faceClassifier =&face;
}

void MouthClassifierProcessor::process(cv::Mat &image)
{
    Mat grayScaled;
    vector<Rect> faces;
    vector<Rect> mouths;
    double reduceFactor = 3;
    resize(image,grayScaled,Size(),1/reduceFactor,1/reduceFactor);
    cvtColor(grayScaled,grayScaled,COLOR_BGR2GRAY);
    faceClassifier->detectMultiScale(grayScaled,faces);
    for(vector<Rect>::iterator it1=faces.begin();it1!=faces.end();it1++){
        it1->y += it1->height/2;
        it1->height /= 2;
        cv::Mat halfFaceRoi = grayScaled(*it1);
        mouthClassifier->detectMultiScale(halfFaceRoi,mouths);
        Rect rect;
        rect.y = 0;
        for(vector<Rect>::iterator it2=mouths.begin();it2!=mouths.end();it2++){
            if(it2->y>rect.y)
                rect = *it2;
        }
        rect.x += it1->x;
        rect.y += it1->y;
        rect.x *= reduceFactor;
        rect.y *= reduceFactor;
        rect.width *= reduceFactor;
        rect.height *= reduceFactor;
        rectangle(image,rect,Scalar(255,0,0));
    }
}
