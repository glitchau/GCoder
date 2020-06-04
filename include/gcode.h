#pragma once
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




	/*
	class G1 {
	private:
		int x;
		int y;
		int z;
	};
	*/
};