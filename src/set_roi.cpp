/*
 * set_roi.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: gustavo
 */

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <string>
#include <stdio.h>


#include "sensor.h"

using namespace cv;
using namespace std;


vector<Point> trainedPoints;
string winName;
Mat frame, frame_pts;

static void on_mouse( int event, int x, int y, int /*flags*/, void* );

int main(int ac, char** av){

	if (ac != 2){
		cout << "error" << endl;
		return 1;
	}

	string filename = av[1];

	cout << endl << "Reading file: " << filename<< endl;
	FileStorage fs;
	fs.open(filename, FileStorage::READ);

	Sensor sensor;

	fs["Sensor"] >> sensor;

	cout << "MyData = " << endl << sensor << endl << endl;

	VideoCapture cap(sensor.source);

	if (!cap.isOpened())
	{
		cout  << "Could not open source " << sensor.source << endl;
		return -1;
	}

	winName = sensor.name;
	namedWindow(winName, 1);

	cap >> frame;

	imshow(winName, frame);

	cout << "Enter: Select current frame. Space: View next frame" << endl;

	int keyboard = waitKey(0);

	cout << "Key=" << int((char)keyboard) << endl;
	while ((char)keyboard == 32){
		cap >> frame;
		imshow(winName, frame);
		keyboard = waitKey(0);
	}

	setMouseCallback(winName, on_mouse );

	keyboard = waitKey(0);

	cout << "Selected points: " << endl;
	for( size_t i = 0; i < trainedPoints.size(); i++ )
	{
		cout << trainedPoints[i].x << " " << trainedPoints[i].y << endl;
	}

}

static void on_mouse( int event, int x, int y, int /*flags*/, void* ){
    if( frame_pts.empty() )
        return;

    int updateFlag = 0;

    if( event == EVENT_LBUTTONUP ){
        trainedPoints.push_back( Point(x,y) );
        updateFlag = true;
    }

    if( event == EVENT_RBUTTONUP ){
		trainedPoints.clear();
		updateFlag = true;
		frame.copyTo(frame_pts);
	}

    //draw
    if( updateFlag ){
        if (trainedPoints.size() == 1){
        	circle( frame_pts, trainedPoints[0], 5, Scalar(255,20,20) );
        }
        else if (trainedPoints.size() > 1){
        	frame.copyTo(frame_pts);
        	for( size_t i = 0; i < trainedPoints.size() - 1; i++ ){
				line(frame_pts, trainedPoints[i], trainedPoints[i+1], Scalar(255,20,20), 1);
			}
        	line(frame_pts, trainedPoints[trainedPoints.size() - 1], trainedPoints[0], Scalar(255,20,20), 1);
        }

        // draw points
        for( size_t i = 0; i < trainedPoints.size(); i++ ){
        	circle( frame_pts, trainedPoints[i], 5, Scalar(255,20,20) );
        }

        imshow(winName,frame_pts );
   }
}


