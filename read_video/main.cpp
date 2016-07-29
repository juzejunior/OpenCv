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
	cap.open("noromeo.mp4");
	
	namedWindow("Video", 1);
	
	for(;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		imshow("Video", frame);
		if(waitKey(30) >= 0) break;
	}
	// Release the camera or video cap
	cap.release();
	//wait for key
	return 0;
}
