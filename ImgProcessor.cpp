#include "ImgProcessor.h"

using namespace std;
using namespace cv;

ImgProcessor::ImgProcessor()
{
	 //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); exit(1); };
    mask = imread("mask.jpg", CV_LOAD_IMAGE_COLOR);
    if(! mask.data ){ printf("--(!)Error loading mask\n"); exit(1); }
}

/** @function find_face */
Mat ImgProcessor::find_face(Mat frame, Size size){


    cvtColor( frame, frame_gray, CV_8UC1 );

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

    // face region
    Rect region(x,y,w,h);

    Mat res_frame(size, CV_8UC3);
    Mat croped_region, croped_face;
    res_frame.setTo(Scalar(255, 255, 255));
    frame(region).copyTo(croped_region);
    croped_face = crop_face(croped_region, x,y,w,h);
    croped_face.copyTo(res_frame(region));
    return res_frame;
}

/** @function crop_face */
Mat ImgProcessor::crop_face(Mat region, int x, int y, int w, int h)
{
    resize(mask, mask, region.size());
    Mat face(region.size(), CV_8UC3);
    face.setTo(255);
    region.copyTo(face, mask);
    imshow("Croped", face);
    return face;

}