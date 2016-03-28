#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

#include "sensor.h"

using namespace cv;
using namespace std;


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
}
