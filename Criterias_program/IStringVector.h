#pragma once
#include "Vector.hpp"
#include <fstream>
#include <vector>

class IStringVector
{
protected:
	std::vector<char*> context;
	int getResultOfCurrentFunc(std::ifstream& ifs, int functionType, int argument, int elementCount) const;
public:
	IStringVector(std::vector<char*> _context);
	virtual int operator()(int argument) const = 0;
	bool isDefined(int argument) const;
	virtual ~IStringVector() = default;
};