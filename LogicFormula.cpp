#include "LogicFormula.hpp"
#include <typeinfo>


//TODO: tree destruction


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

bool LogicFormula::operator==(LogicFormula& rhs) const
{
	if (typeid(*this) != typeid(rhs)) return false;

	if (leftOperand == nullptr ^ rhs.leftOperand == nullptr) return false;
	if (rightOperand == nullptr ^ rhs.rightOperand == nullptr) return false;
	if (leftOperand == nullptr && rightOperand == nullptr) return true;

	return (*leftOperand == *rhs.leftOperand && *rightOperand == *rhs.rightOperand);
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

bool PropositionalVariable::operator==(PropositionalVariable& rhs) const
{
	return this->name == rhs.name;
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
	if (typeid(*rightOperand) == typeid(*this))
	{
		return rightOperand->getRight.simplify();
	}
	if (typeid(*rightOperand) == typeid(AndFormula))
	{
		LogicFormula* left = rightOperand->getLeft();
		LogicFormula* right = rightOperand->getRight();
		LogicFormula* result = new OrFormula(new NotFormula(left), new NotFormula(right));
		result->simplify();
		return result;
	}
	if (typeid(*rightOperand) == typeid(OrFormula))
	{
		LogicFormula* left = rightOperand->getLeft();
		LogicFormula* right = rightOperand->getRight();
		LogicFormula* result = new AndFormula(new NotFormula(left), new NotFormula(right));
		result->simplify();
		return result;
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