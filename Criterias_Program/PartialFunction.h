#pragma once
class PartialFunction
{
private:
	int(*func)(int) = nullptr;
public:
	PartialFunction() = default;
	PartialFunction(int(*_func)(int)) : func(_func) {}

	virtual int operator()(int argument) const = 0;
	virtual bool isDefined(int argument) const = 0;

	virtual PartialFunction* clone() const = 0;

	virtual ~PartialFunction() = default;
};