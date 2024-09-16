#pragma once
#include "IStringVector.h"
class MinOfCriterias : public IStringVector
{
public:
	MinOfCriterias(std::vector<char*> context);
	int operator()(int argument) const override;
};