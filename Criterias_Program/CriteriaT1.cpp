#include "CriteriaT1.h"
#include <iostream>

CriteriaT1::CriteriaT1(std::vector<int> context) : INumberVector(context)
{}

int CriteriaT1::operator()(int argument) const
{
    for (int i = 0; i < context.size(); i++)
        if(!isDefined(argument))
            throw std::invalid_argument("The function is not defined for this argument.");

    return argument;
}

bool CriteriaT1::isDefined(int argument) const
{
    for (int i = 0; i < context.size(); i++)
    {
        if (argument == context[i])
            return false;
    }
    return true;
}
