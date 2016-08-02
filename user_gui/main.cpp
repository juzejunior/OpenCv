#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	//criando as imagens
	Mat robot = imread("stuart.jpg");
	Mat img = imread("big_robot.jpg");
	
	//criando as janelas
	namedWindow("Stuart", WINDOW_NORMAL);
	namedWindow("Big Robot", WINDOW_AUTOSIZE);
	
	//movendo as janelas
	moveWindow("Stuart", 10, 10);
	moveWindow("Big Robot", 510, 10);
	
	//redimensionando o tamanho da janela, so funciona para imagens não auto
	resizeWindow("Stuart", 512, 512);
	
	//exibindo as imagens
	imshow("Stuart", robot);
	imshow("Big Robot", img);
	
	waitKey(0);
	
	//destruindo as janelas
	destroyWindow("Stuart");
	destroyWindow("Big Robot");
	
	/* Create 10 windows
	for(int i =0; i< 10; i++)
	{
		ostringstream ss;
		ss << "Photo " << i;	
		namedWindow(ss.str());
		moveWindow(ss.str(), 20*i, 20*i);
		imshow(ss.str(), photo);	
	}
	waitKey(0);
	// Destroy all windows
	destroyAllWindows();
	return 0*/
	
	return 0;
}
	
