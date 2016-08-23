#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cv;

/*
 * Project: Recognizer people
 * Author: José Diôgo
 * Based on: Detect_face.cpp opencv
 * */

/** Function Headers */
//Mat detectAndDisplay(Mat frame);
void recordPerson(string personName, Mat face, int cont);

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String face_cascade_name = "cascade/haarcascade_frontalface_alt.xml";
//String face_cascade_name = "cascade/lbpcascade_frontalface.xml";
String profile_cascade_name = "cascade/haarcascade_profileface.xml";
String eyes_cascade_name = "cascade/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier profile_cascade;
string window_name = "Detecção de Face";
//RNG rng(12345);

//to recognize
static void read_csv(const string &filename, std::vector<Mat> &images, std::vector<int> &labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    string line, path, classlabel;
    
    if (!file) {
        string error_message = "Invalid file, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
   
    while (getline(file, line)){
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, char **argv)
{
	string fn_csv = "data/face/diogo/diogo0.jpg;0";
	std::vector<Mat> images;
	std::vector<int> labels;
	int width, height;
	
	//read the data and store in each respective image with label
	try{
	   read_csv(fn_csv, images, labels);	
	}catch(cv::Exception& e){
	  cerr << "Error opening the directory" << fn_csv << "Because: " << e.msg << endl;
	  //ease the mind, and come back later :(
	  exit(1);
	}
	//getting the width & height of first image - VERIFY THE IMAGE IS NOT LOADING
	width = images[0].cols;
	height = images[0].rows;
	
	
	return 0;
}

