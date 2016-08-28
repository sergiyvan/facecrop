#include "ImgProcessor.h"

using namespace std;
using namespace cv;

ImgProcessor::ImgProcessor()
{
	 //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); exit(1); };
    imread("mask.jpg", CV_LOAD_IMAGE_COLOR);
}

Mat ImgProcessor::find_face(Mat frame, Size size){


    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    Rect biggest_face;
    if (faces.size() > 0)
    	biggest_face = faces[0];

    // find biggest face
    for( size_t i = 1; i < faces.size(); i++ )
    {
    	if (faces[i].width * faces[i].height > biggest_face.width * biggest_face.height){
    		biggest_face = faces[i];
    	}
    }

    //draw bigest face
    Point center( biggest_face.x + biggest_face.width/2, biggest_face.y + biggest_face.height/2 );
    //ellipse( frame, center, Size( biggest_face.width/1.5, biggest_face.height/1.0), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    faces.clear();

    int x = biggest_face.x, y = biggest_face.y-padding_y;
    int w = biggest_face.width, h = (int)biggest_face.height+padding_y*1.5;

    Rect region(x,y,w,h);

    Mat res_frame(size, CV_8UC3);
    res_frame.setTo(Scalar(255, 255, 255));
    frame(region).copyTo(res_frame(region));
    get_contours(res_frame, x,y,w,h);
    return res_frame;
}

/** @function thresh_callback */
void ImgProcessor::get_contours(Mat src, int x, int y, int w, int h)
{
    Mat src_gray, canny_output;
    RNG rng(12345);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    // Convert image to gray and blur it
    cvtColor( src, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );
    // Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    // Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0) );

    // Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    drawing.setTo(Scalar(255, 255, 255));
    //drawContours(drawing, contours, -1, Scalar(255,0,0), CV_FILLED);

    // approximate contours
    // std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    // for( int i = 0; i < contours.size(); i++ ) {
    //     approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 5, true );
    // }

    // vector<RotatedRect> minEllipse( contours.size() );
    // int face_size = w*h;
    // for( int i = 0; i < contours.size(); i++ )
    //  {
    //    if( contours[i].size() > 5 )
    //      { minEllipse[i] = fitEllipse( Mat(contours[i]) );
    //         Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    //         int ellipse_size = minEllipse[i].size.width * minEllipse[i].size.height;
    //         if (ellipse_size > 0.7*face_size && ellipse_size < 0.9*face_size && minEllipse[i].angle > -10 && minEllipse[i].angle < 10){
    //             ellipse( drawing, minEllipse[i], color, 2, 8 );
    //         }
    //      }

    //  }

    // for( int i = 0; i < contours.size(); i++ )
    // {
    //     Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    //     // contour
    //     drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );

    // }


    /// Show in a window
    imshow( "Contours", drawing );
}