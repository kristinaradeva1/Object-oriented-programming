#include "IStringVector.h"
#include "CriteriaT1.h"
#include "CriteriaT2.h"
#include "Pair.h"
#include "Vector.hpp"
#include "MaxOfCriterias.h"
#include "MinOfCriterias.h"
#include "CriteriaT0.h"
#include <fstream>
#pragma warning (disable : 4996)

int IStringVector::getResultOfCurrentFunc(std::ifstream& ifs, int functionType, int argument, int elementCount) const
{
	switch (functionType)
	{
	case 0:
	{
		std::vector<Pair<int>> vectorOfPairs(elementCount);
		for (int i = 0; i < elementCount; i++)
			ifs.read((char*)&vectorOfPairs[i].argument, sizeof(int));

		for (int i = 0; i < elementCount; i++)
			ifs.read((char*)&vectorOfPairs[i].result, sizeof(int));

		CriteriaT0 func(vectorOfPairs);
		return func.operator()(argument).result;

		break;
	}
	case 1:
	{
		std::vector<int> vectorOfNums(elementCount);
		ifs.read((char*)vectorOfNums.data(), vectorOfNums.size() * sizeof(int));

		CriteriaT1 func(vectorOfNums);
		return func.operator()(argument);
		break;
	}
	case 2:
	{
		std::vector<int> vectorOfNums(elementCount);
		ifs.read((char*)vectorOfNums.data(), vectorOfNums.size() * sizeof(int));

		CriteriaT2 func(vectorOfNums);
		return func.operator()(argument);
		break;
	}
	case 3:
	{
		std::vector<char*> vectorOfStrings(elementCount);
		char byte;
		char buffer[15];

		for (int i = 0; i < elementCount; i++)
		{
			int iter = 0;
			while (ifs.read(&byte, sizeof(byte)))
			{
				if (byte == '\0')
					break;

				buffer[iter] = byte;
				iter++;
			}
			buffer[iter] = '\0';
			size_t len = strlen(buffer);
			vectorOfStrings[i] = new char[len + 1];
			strcpy(vectorOfStrings[i], buffer);
		}

		MinOfCriterias func(vectorOfStrings);
		return func.operator()(argument);
		break;
	}
	case 4:
	{
		std::vector<char*> vectorOfStrings(elementCount);
		char byte;
		char buffer[15];

		for (int i = 0; i < elementCount; i++)
		{
			int iter = 0;
			while (ifs.read(&byte, sizeof(byte)))
			{
				if (byte == '\0')
					break;

				buffer[iter] = byte;
				iter++;
			}
			buffer[iter] = '\0';
			size_t len = strlen(buffer);
			vectorOfStrings[i] = new char[len + 1];
			strcpy(vectorOfStrings[i], buffer);
		}

		MaxOfCriterias func(vectorOfStrings);
		return func.operator()(argument);
		break;
	}
	}
	return 0;
}

IStringVector::IStringVector(std::vector<char*> _context) : context(_context)
{}

bool IStringVector::isDefined(int argument) const
{
	for (int i = 0; i < context.size(); i++)
	{
		std::ifstream ifs(context[i], std::ios::binary);
		if (!ifs.is_open())
			throw std::runtime_error("The file hasn't been opened!");

		int elementCount;
		ifs.read((char*)&elementCount, sizeof(int));
		int functionType;
		ifs.read((char*)&functionType, sizeof(int));

		switch (functionType)
		{
		case 0:
		{
			std::vector<int> args1(elementCount);
			std::vector<int> res1(elementCount);
			ifs.read((char*)args1.data(), args1.size() * sizeof(int));
			ifs.read((char*)res1.data(), res1.size() * sizeof(int));

			std::vector<Pair<int>> vectorOfPairs(elementCount);
			for (int i = 0; i < elementCount; i++)
			{
				vectorOfPairs[i].argument = args1[i];
				vectorOfPairs[i].result = res1[i];
			}

			CriteriaT0 func(vectorOfPairs);
			if (!func.isDefined(argument))
				return false;
			break;
		}
		case 1:
		{
			std::vector<int> vectorOfNums(elementCount);
			ifs.read((char*)vectorOfNums.data(), vectorOfNums.size() * sizeof(int));

			CriteriaT1 func(vectorOfNums);
			if (!func.isDefined(argument))
				return false;
			break;
		}
		case 2:
		{
			std::vector<int> vectorOfNums(elementCount);
			ifs.read((char*)vectorOfNums.data(), vectorOfNums.size() * sizeof(int));

			CriteriaT2 func(vectorOfNums);
			if (!func.isDefined(argument))
				return false;
			break;
		}
		case 3:
		{

			std::vector<char*> vectorOfStrings(elementCount);
			char byte;
			char buffer[15];

			for (int i = 0; i < elementCount; i++)
			{
				int iter = 0;
				while (ifs.read(&byte, sizeof(byte)))
				{
					if (byte == '\0')
						break;

					buffer[iter] = byte;
					iter++;
				}
				buffer[iter] = '\0';
				size_t len = strlen(buffer);
				vectorOfStrings[i] = new char[len + 1];
				strcpy(vectorOfStrings[i], buffer);
			}

			MinOfCriterias func(vectorOfStrings);
			if (!func.isDefined(argument))
				return false;
			break;
		}
		case 4:
		{
			std::vector<char*> vectorOfStrings(elementCount);
			char byte;
			char buffer[15];

			for (int i = 0; i < elementCount; i++)
			{
				int iter = 0;
				while (ifs.read(&byte, sizeof(byte)))
				{
					if (byte == '\0')
						break;

					buffer[iter] = byte;
					iter++;
				}
				buffer[iter] = '\0';
				size_t len = strlen(buffer);
				vectorOfStrings[i] = new char[len + 1];
				strcpy(vectorOfStrings[i], buffer);
			}

			MaxOfCriterias func(vectorOfStrings);
			if (!func.isDefined(argument))
				return false;
			break;
		}
		}
	}
	return true;
}