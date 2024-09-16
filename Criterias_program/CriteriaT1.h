#pragma once
#include "INumberVector.h"
#include <vector>
class CriteriaT1 : public INumberVector
{
public:
    CriteriaT1(std::vector<int> context);
    int operator()(int argument) const override;
    bool isDefined(int argument) const override;
};