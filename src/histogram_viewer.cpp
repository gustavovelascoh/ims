#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void show_cap_info(VideoCapture cap, std::string input);

int main(int ac, char** av){
	const string source = av[1];

	VideoCapture cap(source);
	namedWindow("Frame",1);
	namedWindow("Histogram",1);

	if (!cap.isOpened())
	{
		cout  << "Could not open reference " << source << endl;
		return -1;
	}

	show_cap_info(cap,source);

	Mat frame, frame_heq, frame_gr;
	int keyboard;

	while( (char)keyboard != 'q' && (char)keyboard != 27 ){
		cap >> frame;
		cout << "Frame# " << cap.get(CV_CAP_PROP_POS_FRAMES) << endl;

		/// Separate the image in 3 places ( B, G and R )
		vector<Mat> bgr_planes;
		split( frame, bgr_planes );
		cout << "split" << endl;
		/// Establish the number of bins
		int histSize = 256;

		/// Set the ranges ( for B,G,R) )
		float range[] = { 0, 256 } ;
		const float* histRange = { range };

		bool uniform = true; bool accumulate = false;

		Mat b_hist, g_hist, r_hist;
		frame.copyTo(frame_gr);

		/// Compute the histograms:
		calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

		// Draw the histograms for B, G and R
		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound( (double) hist_w/histSize );

		Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

		/// Normalize the result to [ 0, histImage.rows ]
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

		/// Draw for each channel
		for( int i = 1; i < histSize; i++ )
		{
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
			   Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			   Scalar( 255, 0, 0), 2, 8, 0  );
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
			   Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			   Scalar( 0, 255, 0), 2, 8, 0  );
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
			   Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			   Scalar( 0, 0, 255), 2, 8, 0  );
		}

		imshow("Histogram",histImage);
		imshow("Frame",frame);

		cout << "posms# " << cap.get(CV_CAP_PROP_POS_MSEC) << endl;
		keyboard = waitKey(30);
	}
}

void show_cap_info(VideoCapture cap, std::string input){
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	std::cout << "Opening file " << input << std::endl;
	std::cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height << std::endl;
	std::cout << "#frames: " << cap.get(CV_CAP_PROP_FRAME_COUNT) << ", fps: " << cap.get(CV_CAP_PROP_FPS) << std::endl;
	std::cout << "posmsec: " << cap.get(CV_CAP_PROP_POS_MSEC) << ",autofocus: " << cap.get(CV_CAP_PROP_AUTOFOCUS) << std::endl;
}
