#pragma once

#include <string>
#include <map>

class ValuesProvider
{
private:
	std::map<std::string, bool> variables;
public:
	ValuesProvider();
	void setValue(std::string varName, bool value);
	void registerVariable(std::string varName);
	bool getValue(std::string varName);
};