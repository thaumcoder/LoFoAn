#pragma once

#include <string>
#include "ValuesProvider.hpp"

//enum LogicOperator {not, and, or, xor, nand, nor, equ, impl, revimpl, nequ, nimpl};

class LogicFormula
{
protected:
	const std::string symbol;
	LogicFormula* leftOperand;
	LogicFormula* rightOperand;

public:
	virtual LogicFormula* toConjunctiveNormalForm() = 0;
	virtual LogicFormula* toDisjunctiveNormalForm() = 0;
	virtual std::string toString();
	virtual LogicFormula* simplify() = 0;
	virtual bool calculateValue() = 0;
	virtual LogicFormula* getLeft();
	virtual LogicFormula* getRight();

	virtual ~LogicFormula();
};

class PropositionalVariable : public LogicFormula
{
private:
	std::string name;
	ValuesProvider* valueProvider;
public:
	PropositionalVariable(std::string name, ValuesProvider* valProvider);
	std::string toString();
	LogicFormula* getLeft();
	LogicFormula* getRight();
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class TrueConstant : public LogicFormula
{
public:
	TrueConstant();
	std::string toString();
	LogicFormula* getLeft();
	LogicFormula* getRight();
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class FalseConstant : public LogicFormula
{
public:
	FalseConstant();
	std::string toString();
	LogicFormula* getLeft();
	LogicFormula* getRight();
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class NotFormula : public LogicFormula
{
public:
	NotFormula(LogicFormula* op);
	std::string toString();
	LogicFormula* getLeft();
	LogicFormula* getRight();
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};


class AndFormula : public LogicFormula
{
public:
	AndFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class OrFormula : public LogicFormula
{
public:
	OrFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class XorFormula : public LogicFormula
{
public:
	XorFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class NandFormula : public LogicFormula
{
public:
	NandFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class EquFormula : public LogicFormula
{
public:
	EquFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class ImplFormula : public LogicFormula
{
public:
	ImplFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class RevimplFormula : public LogicFormula
{
public:
	RevimplFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class NeqFormula : public LogicFormula
{
public:
	NeqFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

class NimplFormula : public LogicFormula
{
public:
	NimplFormula(LogicFormula* leftOp, LogicFormula* rightOp);
	LogicFormula* simplify();
	bool calculateValue();
	LogicFormula* toConjunctiveNormalForm();
	LogicFormula* toDisjunctiveNormalForm();
};

