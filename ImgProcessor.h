#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class ImgProcessor {
	public:
		ImgProcessor();
	    Mat find_face(Mat frame, Size size);
	    void get_contours(Mat src, int x, int y, int w, int h);
	    void crop_face();
	private:
		String face_cascade_name = "haarcascade_frontalface_alt.xml";
		CascadeClassifier face_cascade;
		Mat frame_gray;
		vector<Rect> faces;
		int padding_y = 80;
	    int thresh = 30;
	    Mat mask;
};