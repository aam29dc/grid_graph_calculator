#include "config_parser.hpp"

std::map<std::string, std::any> variables;

/*
	"width=500;height=400;"
*/
void readConfigFile(const std::string& loc) {
	std::ifstream file;
	file.open(loc);
	if (file.is_open()) {
			//ignore spaces, read alphabet chars until =
				//check if variable exist
					//if variable exist get number after =
					//set variable to number after =
			//start again after hitting ';', until EOF
		
	}
	file.close();

	//initVariableMap();

	//setVariable("width", (int)555);
}

void initVariableMap() {
	/*
	variables["width"] = (int)App::getApp()->getWidth();
	variables["height"] = (int)App::getApp()->getHeight();
	*/
}

void setVariable(std::string& var, std::any& val) {
	if (variables.find(var) == variables.end()) {
		//std::cout << "Unknown variable: " << var << ". ";
		return;
	}
	variables[var] = val;
}