#include "LogicFormula.hpp"
#include <typeinfo>


//TODO: tree destruction
//TODO: implement toConjunctiveNormalForm()
//TODO: implement toDisjunctiveNormalForm()


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
	if (typeid(*leftOperand) == typeid(TrueConstant))
	{
		if (typeid(*rightOperand) == typeid(TrueConstant))
		{
			return new TrueConstant();
		}
		else
		{
			return rightOperand;
		}
	}
	if (typeid(*rightOperand) == typeid(TrueConstant))
	{
		return leftOperand;
	}

	if (typeid(*leftOperand) == typeid(FalseConstant) || typeid(*rightOperand) == typeid(FalseConstant))
	{
		return new FalseConstant();
	}

	return this;
}

bool AndFormula::calculateValue()
{
	return leftOperand->calculateValue() && rightOperand->calculateValue();
}
LogicFormula* AndFormula::toConjunctiveNormalForm()
{
	return nullptr;
}
LogicFormula* AndFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




OrFormula::OrFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* OrFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(FalseConstant))
	{
		if (typeid(*rightOperand) == typeid(FalseConstant))
		{
			return new FalseConstant();
		}
		else
		{
			return rightOperand;
		}
	}
	if (typeid(*rightOperand) == typeid(FalseConstant))
	{
		return leftOperand;
	}

	if (typeid(*leftOperand) == typeid(TrueConstant) || typeid(*rightOperand) == typeid(TrueConstant))
	{
		return new TrueConstant();
	}

	return this;
}

bool OrFormula::calculateValue()
{
	return leftOperand->calculateValue() || rightOperand->calculateValue();
}

LogicFormula* OrFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* OrFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




XorFormula::XorFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* XorFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(TrueConstant) && typeid(*rightOperand) == typeid(TrueConstant))
	{
		return new FalseConstant();
	}
	if (typeid(*leftOperand) == typeid(FalseConstant) && typeid(*rightOperand) == typeid(FalseConstant))
	{
		return new FalseConstant();
	}

	if (typeid(*leftOperand) == typeid(TrueConstant) || typeid(*leftOperand) == typeid(FalseConstant))
	{
		return rightOperand;
	}
	if (typeid(*rightOperand) == typeid(TrueConstant) || typeid(*rightOperand) == typeid(FalseConstant))
	{
		return leftOperand;
	}

	return this;
}

bool XorFormula::calculateValue()
{
	return leftOperand->calculateValue() ^ rightOperand->calculateValue();
}

LogicFormula* XorFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* XorFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




NandFormula::NandFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* NandFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(TrueConstant))
	{
		if (typeid(*rightOperand) == typeid(TrueConstant))
		{
			return new FalseConstant();
		}
		else
		{
			return new NotFormula(rightOperand);
		}
	}
	if (typeid(*rightOperand) == typeid(TrueConstant))
	{
		return new NotFormula(leftOperand);
	}

	if (typeid(*leftOperand) == typeid(FalseConstant) || typeid(*rightOperand) == typeid(FalseConstant))
	{
		return new TrueConstant();
	}

	return this;
}

bool NandFormula::calculateValue()
{
	return !(leftOperand->calculateValue() && rightOperand->calculateValue());
}

LogicFormula* NandFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* NandFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




NorFormula::NorFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* NorFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(FalseConstant))
	{
		if (typeid(*rightOperand) == typeid(FalseConstant))
		{
			return new TrueConstant();
		}
		else
		{
			return new NotFormula(rightOperand);
		}
	}
	if (typeid(*rightOperand) == typeid(FalseConstant))
	{
		return new NotFormula(leftOperand);
	}

	if (typeid(*leftOperand) == typeid(TrueConstant) || typeid(*rightOperand) == typeid(TrueConstant))
	{
		return new FalseConstant();
	}

	return this;
}
bool NorFormula::calculateValue()
{
	return !(leftOperand->calculateValue() || rightOperand->calculateValue());
}
LogicFormula* NorFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* NorFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




EquFormula::EquFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* EquFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(TrueConstant) && typeid(*rightOperand) == typeid(TrueConstant)) return new TrueConstant();
	if (typeid(*leftOperand) == typeid(FalseConstant) && typeid(*rightOperand) == typeid(FalseConstant)) return new TrueConstant();

	if (typeid(*leftOperand) == typeid(TrueConstant) || typeid(*leftOperand) == typeid(TrueConstant)) return  rightOperand;
	if (typeid(*rightOperand) == typeid(TrueConstant) || typeid(*rightOperand) == typeid(TrueConstant)) return  leftOperand;

	return this;
}

bool EquFormula::calculateValue()
{
	return leftOperand->calculateValue() == rightOperand->calculateValue();
}

LogicFormula* EquFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* EquFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}

ImplFormula::ImplFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* ImplFormula::simplify()
{
	if (typeid(*rightOperand) == typeid(FalseConstant))
	{
		if (typeid(*leftOperand) == typeid(FalseConstant)) return new TrueConstant();
		if (typeid(*leftOperand) == typeid(TrueConstant)) return new FalseConstant();
	}
	else if (typeid(*rightOperand) == typeid(TrueConstant))
	{
		return new TrueConstant();
	}

	if (typeid(*leftOperand) == typeid(FalseConstant)) return new TrueConstant();
	if (typeid(*leftOperand) == typeid(TrueConstant)) return rightOperand;

	return this;
}

bool ImplFormula::calculateValue()
{
	bool leftVal = leftOperand->calculateValue();
	if (leftVal == false) return true;

	return rightOperand->calculateValue();
}

LogicFormula* ImplFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* ImplFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




RevimplFormula::RevimplFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* RevimplFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(FalseConstant))
	{
		if (typeid(*rightOperand) == typeid(FalseConstant)) return new TrueConstant();
		if (typeid(*rightOperand) == typeid(TrueConstant)) return new FalseConstant();
	}
	else if (typeid(*leftOperand) == typeid(TrueConstant))
	{
		return new TrueConstant();
	}

	if (typeid(*rightOperand) == typeid(FalseConstant)) return new TrueConstant();
	if (typeid(*rightOperand) == typeid(TrueConstant)) return leftOperand;

	return this;
}

bool RevimplFormula::calculateValue()
{
	bool rightVal = rightOperand->calculateValue();
	if (rightVal == false) return true;

	return leftOperand->calculateValue();
}
LogicFormula* RevimplFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* RevimplFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




NeqFormula::NeqFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* NeqFormula::simplify()
{
	if (typeid(*leftOperand) == typeid(TrueConstant) && typeid(*rightOperand) == typeid(TrueConstant)) return new FalseConstant();
	if (typeid(*leftOperand) == typeid(FalseConstant) && typeid(*rightOperand) == typeid(FalseConstant)) return new FalseConstant();

	if (typeid(*leftOperand) == typeid(TrueConstant) || typeid(*leftOperand) == typeid(TrueConstant)) return  new NotFormula(rightOperand);
	if (typeid(*rightOperand) == typeid(TrueConstant) || typeid(*rightOperand) == typeid(TrueConstant)) return  new NotFormula(leftOperand);

	return this;
}

bool NeqFormula::calculateValue()
{
	return !(leftOperand->calculateValue() == rightOperand->calculateValue());
}

LogicFormula* NeqFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* NeqFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}




NimplFormula::NimplFormula(LogicFormula* leftOp, LogicFormula* rightOp)
{
	leftOperand = leftOp;
	rightOperand = rightOp;
}

LogicFormula* NimplFormula::simplify()
{
	if (typeid(*rightOperand) == typeid(FalseConstant))
	{
		if (typeid(*leftOperand) == typeid(FalseConstant)) return new FalseConstant();
		if (typeid(*leftOperand) == typeid(TrueConstant)) return new TrueConstant();
	}
	else if (typeid(*rightOperand) == typeid(TrueConstant))
	{
		return new FalseConstant();
	}

	if (typeid(*leftOperand) == typeid(FalseConstant)) return new TrueConstant();
	if (typeid(*leftOperand) == typeid(TrueConstant)) return new NotFormula(rightOperand);

	return this;
}

bool NimplFormula::calculateValue()
{
	bool leftVal = leftOperand->calculateValue();
	if (leftVal == false) return false;

	return !rightOperand->calculateValue();
}

LogicFormula* NimplFormula::toConjunctiveNormalForm()
{
	return nullptr;
}

LogicFormula* NimplFormula::toDisjunctiveNormalForm()
{
	return nullptr;
}