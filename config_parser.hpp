#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <map>
#include <string>
#include <any>
#include <fstream>

extern std::map<std::string, std::any> variables;

void readConfigFile(const std::string& loc);
	
void initVariableMap();

void setVariable(std::string& var, std::any& val);

#endif