#pragma once
#include "IStringVector.h"
class MaxOfCriterias : public IStringVector
{
public:
	MaxOfCriterias(std::vector<char*> context);
	int operator()(int argument) const override;
};