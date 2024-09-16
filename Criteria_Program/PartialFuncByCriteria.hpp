#pragma once
#include <iostream>
#include "PartialFunction.h"
#include <vector>
#include "Pair.h"
template<class Func>
class PartialFuncByCriteria : public PartialFunction
{
private:
	Func function;
public:
	PartialFuncByCriteria(const Func& _function) : PartialFunction(function), function(_function) {}

	int operator()(int argument) const override;
	bool isDefined(int argument) const override;

	PartialFunction* clone() const override;

	~PartialFunction() override = default;
};

template<class Func>
int PartialFuncByCriteria<Func>::operator()(int argument) const
{
	if (isDefined(argument))
		return function(argument);
	else
		throw std::invalid_argument("The function is not defined for this argument.");
}

template<class Func>
bool PartialFuncByCriteria<Func>::isDefined(int argument) const
{
	for (int i = 0; i < function.context.size; i++)
	{
		if (argument == function.context[i].argument)
			return true;
	}
	return false;
}

template<class Func>
PartialFunction* PartialFuncByCriteria<Func>::clone() const
{
	return new PartialFuncByCriteria(*this);
}