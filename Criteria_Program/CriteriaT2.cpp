#include "CriteriaT2.h"
#include <iostream>

CriteriaT2::CriteriaT2(std::vector<int> context) : INumberVector(context)
{}

int CriteriaT2::operator()(int argument) const
{
    if (!isDefined(argument))
        throw std::invalid_argument("The function is not defined for this argument.");

    for (int i = 0; i < context.size(); i++)
    {
        if (context[i] == argument)
            return 1;
    }
    return 0;
}

bool CriteriaT2::isDefined(int argument) const
{
    return true;
}
