#include <cstdlib>
#include <iostream>
#include <string>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

int main(){
	Mat cameraFeed;
	
	VideoCapture capture;

	capture.open(0);
	
	

	if (!capture.isOpened()){
		cout << "Not opened";
		return -1;
	}

	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	while (true){
		if (!capture.read(cameraFeed))
		{
			cout << "Waiting for successful read";
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		
		if (cameraFeed.empty()){
			cout << "Empty cameraFeed";
			continue;
		}
		imshow("image", cameraFeed);

		waitKey(30);
	}
}