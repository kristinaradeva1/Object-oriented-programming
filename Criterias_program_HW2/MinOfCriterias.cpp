#include "MinOfCriterias.h"
#include "CriteriaT1.h"
#include "CriteriaT2.h"
#include "Pair.h"
#include "Vector.hpp"
#include "MaxOfCriterias.h"
#include "CriteriaT0.h"
#include <fstream>

MinOfCriterias::MinOfCriterias(std::vector<char*> context) : IStringVector(context)
{}

int MinOfCriterias::operator()(int argument) const
{
	if (!isDefined(argument))
		throw std::invalid_argument("The function is not defined for this argument.");

	int minOfFuncs = INT_MAX;
	for (int i = 0; i < context.size(); i++)
	{
		std::ifstream ifs(context[i], std::ios::binary);
		if (!ifs.is_open())
			throw std::runtime_error("The file hasn't been opened!");

		int elementCount;
		ifs.read((char*)&elementCount, sizeof(int));
		int functionType;
		ifs.read((char*)&functionType, sizeof(int));

		int curResult = getResultOfCurrentFunc(ifs, functionType, argument, elementCount);
		if (curResult < minOfFuncs)
			minOfFuncs = curResult;
	}
	return minOfFuncs;
}