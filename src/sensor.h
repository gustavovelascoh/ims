/*
 * Sensor.h
 *
 *  Created on: Mar 12, 2016
 *      Author: gustavo
 */
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class Sensor{
public: Sensor() : sensor_type(),
		data_type(), source(),
		name(){}
	void write(FileStorage& fs) const {
		fs << "{" << "sensor_type" << sensor_type;
		fs << "data_type" << data_type;
		fs << "source" << source;
		fs << "name" << name;
		fs << "}";
	}
	void read (const FileNode& node){
		sensor_type = (int) node["sensor_type"];
		data_type = (int) node["data_type"];
		source = (string) node["source"];
		name = (string) node["name"];
	}
public:
	int sensor_type;
	int data_type;
	string source;
	string name;
};

//These write and read functions must be defined for the serialization in FileStorage to work
static void write(FileStorage& fs, const std::string&, const Sensor& x)
{
    x.write(fs);
}
static void read(const FileNode& node, Sensor& x, const Sensor& default_value = Sensor()){
    if(node.empty())
        x = default_value;
    else
        x.read(node);
}

// This function will print our custom class to the console
static ostream& operator<<(ostream& out, const Sensor& s)
{
    out << "{ sensor_type = " << s.sensor_type << ", ";
    out << "data_type = " << s.data_type << ", ";
    out << "source = " << s.source << ", ";
    out << "name = " << s.name << "}";
    return out;
}



