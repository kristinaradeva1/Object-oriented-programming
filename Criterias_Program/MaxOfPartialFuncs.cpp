#include "MaxOfPartialFuncs.h"
#include <iostream>
bool MaxOfPartialFuncs::isDefined(int argument) const
{
	for (int i = 0; i < partialFuncsCount; i++)
	{
		if (!partialFuncs[i]->isDefined(argument))
			return false;
	}
	return true;
}

int MaxOfPartialFuncs::operator()(int argument) const
{
	if (!isDefined(argument))
		throw std::invalid_argument("The function is not defined for this argument.");

	int biggestResult = INT_MIN;
	for (int i = 0; i < partialFuncsCount; i++)
	{
		if (partialFuncs[i]->operator()(argument) > biggestResult)
			biggestResult = partialFuncs[i]->operator()(argument);
	}
	return biggestResult;
}

PartialFunction* MaxOfPartialFuncs::clone() const
{
	return new MaxOfPartialFuncs(*this);
}
