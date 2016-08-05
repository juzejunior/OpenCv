#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <QCheckBox>
#include <QLabel>
#include <QLineButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace cv;
using namespace std;

//salva a posicao 
int blurAmount = 15;

bool applyGray = false;
bool applyBlur = false;
bool applySobel = false;
//quando ocorre alteracao chame 
static void onChange(int pos, void* userInput);
//callbacks
void grayCallback(int state, void* userData);
void bgrCallback(int state, void* userData);
void sobelCallback(int state, void* userData);
//aplica os efeitos
void applyFilters();

//ouve a interacao do mouse
static void onMouse(int event, int x, int y, int, void* userInput);

int main(int argc, char **argv)
{
	Mat stuart = imread("stuart.jpg");
	
	namedWindow("Stuart", WINDOW_NORMAL);
	
	//criando botoes
	createButton("Blur", blurCallback, NULL, QT_CHECKBOX, 0);
	createButton("Gray", grayCallback, NULL, QT_RADIOBOx, 0);
	createButton("RGB", bgrCallback, NULL, QT_RADIOBOX, 1);
	
	//efeito sobel
	createButton("Sobel", sobelCallback, NULL, QT_PUSH_BUTTON, 0);
	
	//wait key
	waitKey(0);
	
	destroyWindow("Stuart");
	/*criando um trackbar - um ajustador
	createTrackbar("Stuart","Stuart",&blurAmount, 30, onChange, &stuart);
	setMouseCallback("Stuart",onMouse, &stuart);
	//chame onchange para iniciar
	onChange(blurAmount, &stuart);*/
	
	return 0;
}

void grayCallback(int state, void* userData)
{
		applyGray = true;
		applyFilters();
}

void bgrCallback(int state, void* userData)
{
	applyGray = false;
	applyFilters();
}

void applyFilters()
{
	Mat result;
	stuart.copyTo(result);
	
	if(applyGray) cvtColor(result, result, COLOR_BGR2GRAY);
	
	if(applyBlur) blur(result, result, Size(5,5));
	
	if(applySobel) Sobel(result, result, CV_8U, 1, 1);
	
	imshow("Stuart", result);
}


void blurCallback(int state, void* userData)
{
	applyBlur = (bool) state;
	applyFilters();
}

static void onChange(int pos, void* userInput)
{
	//nós nao podemos aplicar 0 no filtro
	if(pos <= 0) return;
	//imagem para o resultado
	Mat imgBlur;
	Mat *img = (Mat*) userInput;	
	//aplicando o filtro blur
	blur(*img, imgBlur, Size(pos,pos));
	
	imshow("Stuart", imgBlur);
}
//no click do mouse
static void onMouse(int event, int x, int y, int, void* userInput)
{
	if(event != EVENT_LBUTTONDOWN) return;
	//pegando a imagem
	Mat *img = (Mat*) userInput; 
	//desenhando um circulo
	//circle(*img, Point(x,y), 10, Scalar(0,255,0), 3);
	//blur na imagem
	onChange(blurAmount, img);
}
