#pragma once
#include "PartialFunction.h"
#include "PartialFunctionCollection.h"

class MaxOfPartialFuncs : public PartialFunctionCollection
{
public:
	bool isDefined(int argument) const override;
	int operator()(int argument) const override;

	PartialFunction* clone() const override;
};