#include "MinOfPartialFuncs.h"
#include <iostream>
bool MinOfPartialFuncs::isDefined(int argument) const
{
	for (int i = 0; i < partialFuncsCount; i++)
	{
		if (!partialFuncs[i]->isDefined(argument))
			return false;
	}
	return true;
}

int MinOfPartialFuncs::operator()(int argument) const
{
	if (!isDefined(argument))
		throw std::invalid_argument("The function is not defined for this argument.");

	int smallestResult = INT_MAX;
	for (int i = 0; i < partialFuncsCount; i++)
	{
		if (partialFuncs[i]->operator()(argument) < smallestResult)
			smallestResult = partialFuncs[i]->operator()(argument);
	}
	return smallestResult;
}

PartialFunction* MinOfPartialFuncs::clone() const
{
	return new MinOfPartialFuncs(*this);
}
