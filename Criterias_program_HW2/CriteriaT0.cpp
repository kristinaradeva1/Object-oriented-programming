#include "CriteriaT0.h"
#include <iostream>
#include "Pair.h"

CriteriaT0::CriteriaT0(std::vector<Pair<int>> _context) : context(_context)
{}

Pair<bool> CriteriaT0::operator()(int argument) const
{
    if (!isDefined(argument))
        throw std::invalid_argument("The function is not defined for this argument.");

    for (int i = 0; i < context.size(); i++)
    {
        if (context[i].argument == argument)
            return Pair<bool>(true, context[i].result);
    }
}

bool CriteriaT0::isDefined(int argument) const
{
    for (int i = 0; i < context.size(); i++)
    {
        if (context[i].argument == argument)
            return true;
    }
    return false;
}