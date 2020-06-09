#ifndef GCODE_H
#define GCODE_H

#include <iostream>
#include <string>
#include <sstream>
#include <yaml-cpp/yaml.h>

typedef std::map<std::string, std::vector<std::string>> GCodeVariables;

class GCode
{
private:
	

public:
	GCode();
	~GCode();

private: //functions
	YAML::Node loadedParameters;
	GCodeVariables gcodeVariables1;

public:
	//std::string GCode::G01(void);
	std::string GCode::G01(int x = NULL);
	void GCode::getList(std::vector<std::string>& v);
	void GCode::getParameters(std::vector<std::string>& v, std::string variable);




	/*
	class G1 {
	private:
		int x;
		int y;
		int z;
	};
	*/
};

#endif