/*
 * create_sensor.cpp
 *
 *  Created on: Mar 2, 2016
 *      Author: gustavo
 */

#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

#include "sensor.h"
using namespace cv;
using namespace std;



int main(int ac, char** av){

    Sensor sensor = Sensor();

    cout << "Select sensor type (0: Camera, 1: Laser, 2: Lidar)[0]:" << endl;
    cin >> sensor.sensor_type;

    cout << "Select data type (0: Stream, 1: Dataset)[1]:" << endl;
    cin >> sensor.data_type;

    cout << "Select data source (file path or URL):" << endl;
    cin >> sensor.source;

    cout << "Select a name for this sensor:" << endl;
    cin >> sensor.name;

    stringstream filename_ss;

    filename_ss << "sensors/" << sensor.name << ".xml";
    //filename_ss << sensor.name << ".xml";

    FileStorage fs(filename_ss.str(), FileStorage::WRITE);

    cout << "Writing to " << filename_ss.str() << " ..." << endl;

    //fs << "Test" << 3;
    fs << "Sensor" << sensor;
    fs.release();
    cout << "Write Done." << endl;

    return 0;
}
