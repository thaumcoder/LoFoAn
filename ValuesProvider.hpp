#pragma once

#include <string>

class ValuesProvider
{
public:
	void registerValue(std::string varName, bool value);
	bool getValue(std::string varName);
};