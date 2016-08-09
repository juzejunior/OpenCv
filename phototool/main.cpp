#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;


const char* keys =
{
	"{help h usage ? | | print this message}"
	"{@image || Image to process}"
};

int main(int argc, char ** argv)
{
	Mat img;
	CommandLineParser parser(argc, argv, keys);
	
	parser.about("PhotoTool v1.0");
	if(parser.has("help"))
	{
		parser.printMessage();
		return 0;
	}
	
	//arquivo recebido
	String File = parser.get<String>(0);
	
	//verifica se o parametro foi passado corretamente
	if(!parser.check())
	{
		parser.printErrors();
		return 0;
	}
	
	img = imread(File);
	//cria a janela
	namedWindow("Input", WINDOW_AUTOSIZE);
	
	//criando os botoes
	createButton("Histogram", showHistoCallback, NULL, QT_PUSH_BUTTON, 0);
	createButton("Lomography", lomoCallback, NULL, QT_PUSH_BUTTON, 0);
	createButton("Cartonize", cartoonCallback, NULL, QT_PUSH_BUTTON, 0);
	
	//exibe a imagem
	imshow("Input", img);
	waitKey(0);
	
	return 0;
}
