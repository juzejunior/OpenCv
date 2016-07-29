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
	//Lendo imagens
	Mat img_color = imread("img/robot.jpg");
	Mat img_gray = imread("img/robot.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	//escrevendo
	imwrite("img/robot_gray.jpg", img_gray);
	
	//pegando o penultimo pixel com as funcoes do opencv
	int myRow=img_color.cols-2;
	int myCol=img_color.rows-2;
	
	cout << myRow << " Col " << myCol << endl;
	
	Vec3b pixel = img_color.at<Vec3b>(myRow, myCol);
	
	cout << "Pixel value (B,G,R): (" << (int)pixel[0] << "," << (int) pixel[1] << "," << (int)pixel[2] << ")" << endl;
	
	//exibindo imagens
	imshow("Robot Colorful", img_color);
	imshow("Gray Scale Robot", img_gray);
	
	//wait for key
	waitKey(0);
	return 0;
}
