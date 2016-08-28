#include "ImgProcessor.h"
#include "string"

#include <opencv2/opencv.hpp>
#include "opencv2/videoio.hpp"

using namespace cv;
using namespace std;


int main(int, char**){
    VideoCapture cam(0); // open the default camera
    if(!cam.isOpened()){  // check if we succeeded
        return -1;
    }

    //init output video
    int codec = VideoWriter::fourcc ('F','M','P','4');
    VideoWriter outputVideo;
    const string name = "facecrop.mp4";
    Size size = Size((int) cam.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                     (int) cam.get(CV_CAP_PROP_FRAME_HEIGHT));
    outputVideo.open(name, codec, cam.get(CV_CAP_PROP_FPS)/2, size, true);
    ImgProcessor img_processor;

	for(;;)
    {
        Mat frame;
        cam >> frame; // get a new frame from camera
        // cvtColor(frame, edges, COLOR_BGR2GRAY);
        // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        // Canny(edges, edges, 0, 30, 3);
        try {
            Mat res_frame = img_processor.find_face(frame, size);
            //-- Show what you got
            imshow("Camera", res_frame);
            outputVideo << res_frame;
        } catch (...) { /*  */ }
        if(waitKey(27) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}