#include "LogicFormula.hpp"
#include <typeinfo>





std::string LogicFormula::toString()
{
	return (leftOperand->toString() + symbol + rightOperand->toString());
}

LogicFormula* LogicFormula::getLeft()
{
	return leftOperand;
}

LogicFormula* LogicFormula::getRight()
{
	return rightOperand;
}



PropositionalVariable::PropositionalVariable(std::string name, ValuesProvider* valProvider) : name(name), valueProvider(valProvider)
{

}

std::string PropositionalVariable::toString()
{
	return name;
}

LogicFormula* PropositionalVariable::getLeft()
{
	return nullptr;
}

LogicFormula* PropositionalVariable::getRight()
{
	return nullptr;
}

LogicFormula* PropositionalVariable::simplify()
{
	return this;
}

bool PropositionalVariable::calculateValue()
{
	return valueProvider->getValue(name);
}

LogicFormula* PropositionalVariable::toConjunctiveNormalForm()
{
	return this;
}

LogicFormula* PropositionalVariable::toDisjunctiveNormalForm()
{
	return this;
}




TrueConstant::TrueConstant()
{

}

std::string TrueConstant::toString()
{
	return symbol;
}

LogicFormula* TrueConstant::getLeft()
{
	return nullptr;
}

LogicFormula* TrueConstant::getRight()
{
	return nullptr;
}

LogicFormula* TrueConstant::simplify()
{
	return this;
}

bool TrueConstant::calculateValue()
{
	return true;
}

LogicFormula* TrueConstant::toConjunctiveNormalForm()
{
	return this;
}

LogicFormula* TrueConstant::toDisjunctiveNormalForm()
{
	return this;
}




FalseConstant::FalseConstant()
{
	leftOperand = nullptr;
	rightOperand = nullptr;
}

std::string FalseConstant::toString()
{
	return symbol;
}

LogicFormula* FalseConstant::simplify()
{
	return this;
}

bool FalseConstant::calculateValue()
{
	return false;
}

LogicFormula* FalseConstant::toConjunctiveNormalForm()
{
	return this;
}
LogicFormula* FalseConstant::toDisjunctiveNormalForm()
{
	return this;
}




NotFormula::NotFormula(LogicFormula* op)
{
	rightOperand = op;
	leftOperand = nullptr;
}

std::string NotFormula::toString()
{
	return (symbol + rightOperand->toString());
}

LogicFormula* NotFormula::getLeft()
{
	return nullptr;
}

LogicFormula* NotFormula::getRight()
{
	return rightOperand;
}

LogicFormula* NotFormula::simplify()
{
	if (typeid(rightOperand) == typeid(this))
	{
		return rightOperand->getRight.simplify();
	}
	else
	{
		rightOperand = rightOperand->simplify();
		return rightOperand;
	}
}

bool NotFormula::calculateValue()
{
	return !rightOperand->calculateValue();
}

LogicFormula* NotFormula::toConjunctiveNormalForm()
{
	return nullptr; //TODO: implement
}

LogicFormula* NotFormula::toDisjunctiveNormalForm()
{
	return nullptr; //TODO: implement
}




AndFormula::AndFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* AndFormula::simplify()
{

}

bool calculateValue();
LogicFormula* toConjunctiveNormalForm();
LogicFormula* toDisjunctiveNormalForm();