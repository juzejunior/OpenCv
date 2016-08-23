/**
 * @file objectDetection.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream
 */
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cv;

/** Function Headers */
Mat detectAndDisplay(Mat frame);
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
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
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

/**
 * @function main
 */
int main(void)
{
  VideoCapture capture;
  Mat frame;
  Mat face;
  int cont = 0;
  string nome = "diogo";

  //-- 1. Load the cascades
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if(!profile_cascade.load(profile_cascade_name)){cout << "Error on loading Profile Cascade"; return -1; };
  //-- 2. Read the video stream
  capture.open(-1);
  if( capture.isOpened())
  {
    for(;;)
    {
      capture >> frame;
      //-- 3. Apply the classifier to the frame
      if(!frame.empty()){
		  face = detectAndDisplay(frame);
		  
		 /* if(cont == 0)
		  {
			cout << "Hello, I'm Bill what is your name?" << endl;
			cin >> nome;  
		  }*/
		  if(cont < 10)
		  {
			  //grava a pessoa
			  recordPerson(nome, face, cont);
			  cont++;
	      }else if(cont == 10){
			  cout << "Thanks. Now i know you, see you later!" << endl;
		  }
	  }
      else
      {
		  printf(" --(!) No captured frame -- Break!"); 
		  break; 
      }

      int c = waitKey(10);
      if( (char)c == 'c' ) { break; }
    }
  }
  return 0;
}

/**
 * @function detectAndDisplay
 */
Mat detectAndDisplay(Mat frame)
{
   std::vector<Rect> faces;
   std::vector<Rect> profile_faces;
   Mat frame_gray;
   //convert to gray, to have less colors to worry	
   cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
   //remove noise, using equalization
   equalizeHist(frame_gray, frame_gray);
   //-- Detect frontal faces with cascade
   face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
   
   Rect face_i = faces[0];	
		
   Point center(faces[0].x + faces[0].width/2, faces[0].y + faces[0].height/2);
   rectangle(frame, face_i, CV_RGB(0, 255, 0), 1);
	   
   Mat faceROI = frame_gray(faces[0]);
   //showing the face - Erase later
   //imshow("Face Detected", faceROI);
   std::vector<Rect> eyes;
   //writing some text
   string box_text = format("Pessoa %d", 0);
   //on top left, put some text
   int pos_x = max(face_i.tl().x - 10, 0);
   int pos_y = max(face_i.tl().y - 10, 0);
   //put text on image
   //center: putText(frame, box_text, center , FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);      
   putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);      
   //-- Show what you got
   imshow(window_name, frame);
   
   return faceROI;
}

void recordPerson(string personName, Mat face, int cont)
{
  stringstream ss;
  string name = personName;
  string type = ".jpg";
  string folderName = "data/face/"+personName;
  string folderCreateCommand = "mkdir "+folderName;
  string fullPath;
  
  if(cont == 0) system(folderCreateCommand.c_str());
  
  ss << folderName << "/" << name << cont << type << ";" << 0;
  fullPath = ss.str();
  ss.str("");
  imwrite(fullPath, face);
  	
}




