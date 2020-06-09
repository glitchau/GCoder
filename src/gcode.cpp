#include "gcode.h"

GCode::GCode()
{
	try {
		loadedParameters = YAML::LoadAllFromFile("GCoderParameters.yaml");
	}
	catch (YAML::BadFile e) {
		std::cout << "Could Not Load Bad File : " << e.what() << std::endl;
	}
	catch (YAML::Exception e) {
		std::cout << "Could Not Load Exception : " << e.what() << std::endl;
	}
	std::cout << "GCode" << std::endl;

	std::cout << "size: " << loadedParameters.size() << std::endl;

	YAML::Node temp;
	temp = loadedParameters[0];
	if (temp.IsSequence()) {
		std::cout << "is sequence" << std::endl;
		for (YAML::const_iterator it = temp.begin(); it != temp.end(); ++it) {
			std::cout << it->as<std::string>() << "\n";
		}
	}
	if (temp.IsMap()) {
		std::cout << "is map" << std::endl;
		for (YAML::const_iterator it = temp.begin(); it != temp.end(); ++it) {
			std::string name = it->first.as<std::string>();
			std::cout << name << std::endl;
			YAML::Node temp2 = it->second.as<YAML::Node>();
			std::vector<std::string> tempdata;
			for (YAML::const_iterator it = temp2.begin(); it != temp2.end(); ++it) {
				std::string variable = it->as<std::string>();
				tempdata.push_back(variable);
				std::cout << variable << std::endl;

			}
			//gcodeVariables1.insert("test", std::vector("1","2") );
			gcodeVariables1[name] = tempdata;


		}
		std::cout << "size of gcode" << gcodeVariables1.size() << std::endl;


	}

	for (auto it = gcodeVariables1.begin(); it != gcodeVariables1.end(); ++it) {
		std::cout << it->first << std::endl;
	}

	//std::cout << loadedParameters.begin()->as<>().c_str() << std::endl;

	//load list of GCodeOptions
	//parser? XML?
}

GCode::~GCode()
{
	//std::cout << "Killer Process" << std::endl;
}



/*
std::string GCode::G01(void) {
	std::stringstream ss;

	ss << "G1";

	return ss.str();
}
*/

void GCode::getList(std::vector<std::string> &v)
{
	for (auto it = gcodeVariables1.begin(); it != gcodeVariables1.end(); ++it) {
		//std::cout << "getList" << it->first << std::endl;
		v.push_back(it->first);
	}
	
}

void GCode::getParameters(std::vector<std::string>& v, std::string variable)
{
	v = gcodeVariables1.find(variable)->second;
}

std::string GCode::G01(int x) {
	std::stringstream ss;

	ss << "G1" << x;

	return ss.str();
}


