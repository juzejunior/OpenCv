//c++
#include <iostream>

//opencv libraries
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"


using namespace cv;
using namespace std;

Mat img;

void showHistoCallback(int state, void* userData);
void lomoCallback(int state, void* userData);
void cartoonCallback(int state, void* userData);
void equalizeCallback(int state, void* userData);

int main(int argc, char ** argv)
{	
	//arquivo recebido
	String File = argv[1];
	
	//verifica se o parametro foi passado corretamente
	img = imread(File);
	if(!img.data)
	{
		cout << "Imagem não encontrada!" << endl;
		return 1;
	}
	
	//cria a janela
	namedWindow("Input", WINDOW_AUTOSIZE);
	
	//criando os botoes
	createButton("Histogram", showHistoCallback, NULL, QT_PUSH_BUTTON, 0);
	createButton("Lomography", lomoCallback, NULL, QT_PUSH_BUTTON, 0);
	createButton("Cartonize", cartoonCallback, NULL, QT_PUSH_BUTTON, 0);
	createButton("Equalize", equalizeCallback, NULL, QT_PUSH_BUTTON, 0);
	//exibe a imagem
	imshow("Input", img);
	waitKey(0);
	
	return 0;
}

void lomoCallback(int state, void* userData)
{
}
void cartoonCallback(int state, void* userData)
{
}

void equalizeCallback(int state, void* userData)
{
	Mat result;
	//convertendo a imagem para YcbCr
	Mat ycrcb;
	cvtColor(img, ycrcb, COLOR_BGR2YCrCb);
	
	//separando a imagem em canais
	Vector<Mat> channels;
	split(ycrcb, channels);
	
	//equaliza o canal Y apenas
	equalizeHist(channels[0], channels[0]);
	//reune o resultado final
	merge(channels, ycrcb);
	//converte novamente para rgb
	cvtColor(ycrcb, result, COLOR_YCrCb2BGR);
	
	//exibe o resultado
	imshow("Equalizada", result);
}

/*histogram callback - calcula o histograma de cada canal(RGB)*/
void showHistoCallback(int state, void* userData)
{
	int width, height, numbins, bStep;
	Mat bHist, gHist, rHist;
	//Separando a imagem em tres canais rgb
	vector<Mat> bgr;
	split(img, bgr);//divide os canais para o vetor bgr
	
	//criando o histograma para 256 bins, o tamanho maximo possivel 0..255
	numbins = 256;
	
	//setando o alcance para BGR, o último número não incluído
	float range[] = {0, 256};
	const float* histRange = {range};

	//calcula o histograma de cada cor(canal - BGR)
	calcHist(&bgr[0], 1, 0, Mat(), bHist, 1, &numbins, &histRange);
	calcHist(&bgr[1], 1, 0, Mat(), gHist, 1, &numbins, &histRange);
	calcHist(&bgr[2], 1, 0, Mat(), rHist, 1, &numbins, &histRange);

	//desenha os histogramas
	//desenha linhas para cada histograma
	width = 512;
	height = 300;
	//cria uma imagem com base cinza
	Mat histImage(height, width, CV_8UC3, Scalar(20,20,20));
	//normalizando a altura máxima do histograma para a altura da imagem
	normalize(bHist, bHist, 0, height, NORM_MINMAX);
	normalize(gHist, bHist, 0, height, NORM_MINMAX);
	normalize(rHist, bHist, 0, height, NORM_MINMAX);

	bStep = cvRound((float) width/(float) numbins);
	
	for(int i= 1; i < numbins; i++)
	{
		//criando as linhas
		line(histImage, 
			Point(bStep*(i-1), height-cvRound(bHist.at<float>(i-1))),
			Point(bStep*(i), height-cvRound(bHist.at<float>(i))),
			Scalar(255, 0, 0));//blue
		
		line(histImage, 
			Point(bStep*(i-1), height-cvRound(gHist.at<float>(i-1))),
			Point(bStep*(i), height-cvRound(gHist.at<float>(i))),
			Scalar(0, 255, 0));//green
		
		line(histImage, 
			Point(bStep*(i-1), height-cvRound(rHist.at<float>(i-1))),
			Point(bStep*(i), height-cvRound(rHist.at<float>(i))),
			Scalar(0, 0, 255));//red
	}
	
	//mostrando o histograma
	imshow("Histogram", histImage);
}

