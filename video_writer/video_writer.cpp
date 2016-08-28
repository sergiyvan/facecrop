#include "video_writer.h"

VideoWritter::VideoWriter(VideoWriter *outputVideo)
{
	this.outputVideo = outputVideo;
}

VideoWriter::write(Mat frame){
	outputVideo << frame;
}