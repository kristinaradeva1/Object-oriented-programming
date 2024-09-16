#pragma once
#include "Pair.h"
#include "Vector.hpp"
#include <vector>
class INumberVector
{
protected:
	std::vector<int> context;
public:
	INumberVector(std::vector<int> _context);
	virtual int operator()(int argument) const = 0;
	virtual bool isDefined(int argument) const = 0;
};