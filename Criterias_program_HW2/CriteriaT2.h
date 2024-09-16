#pragma once
#include "INumberVector.h"

class CriteriaT2 : public INumberVector
{
public:
    CriteriaT2(std::vector<int> context);
    int operator()(int argument) const override;
    bool isDefined(int argument) const override;
};