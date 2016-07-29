#include <iostream>
#include <string>
#include <sstream>
// OpenCV includes
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main(int argc, const char** argv)
{
	VideoCapture cap;
	cap.open(0);
	
	while(true){
		Mat frame;
		cap >> frame;//get frame from camera
		imshow("WebCam", frame);
		if(waitKey(30) >= 0) break;
	}
	//wait for key
	cap.release();
	return 0;
}
