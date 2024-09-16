#pragma once
#include "Pair.h"
#include "Vector.hpp"
#include <vector>

class CriteriaT0
{
private:
	std::vector<Pair<int>> context;

public:
	CriteriaT0(std::vector<Pair<int>> _context);
	Pair<bool> operator()(int argument) const;
	bool isDefined(int argument) const;
};