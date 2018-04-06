#include "ValuesProvider.hpp"

class ValuesProvider
{
private:
	std::map<std::string, bool> variables;
public:
	ValuesProvider();
	void registerVariable(std::string varName);
	void setValue(std::string varName, bool value);
	bool getValue(std::string varName);
};

ValuesProvider::ValuesProvider()
{
	variables = std::map<std::string, bool>();
}

void ValuesProvider::registerVariable(std::string varName)
{
	variables.emplace(varName, false);
}

void ValuesProvider::setValue(std::string varName, bool value)
{
	variables.at(varName) = value;
}

bool ValuesProvider::getValue(std::string varName)
{
	return variables.at(varName);
}