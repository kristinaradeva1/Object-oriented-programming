#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Pair.h"
#include "CriteriaT0.h"
#include "CriteriaT1.h"
#include "CriteriaT2.h"
#include "MinOfCriterias.h"
#include "MaxOfCriterias.h"
#include <vector>
#pragma warning (disable : 4996)

int main()
{
	//std::cout << "Select the mode of the program: 1 or 2: ";
	//int mode;
	//std::cin >> mode;

	//int num1; 
	//std::cin >> num1;
	//int num2;
	//std::cin >> num2;
	//int biggerNum = num1 > num2 ? num1 : num2;
	//int smallerNum = num1 < num2 ? num1 : num2;

	std::ofstream ofs("func.dat", std::ios::binary);
	if (!ofs.is_open())
		throw std::runtime_error("The file hasn't been opened!");

	int num12 = 3;
	int num22 = 3;

	//std::vector<const char*> strs = { "file.dat", "second.dat", "third.dat" };
	//std::vector<int> args = { 3, 5 };
	//std::vector<int> args = { 0, 5, 6, 7 };
	//std::vector<int> args = { 0, 1, 2, 3, 5, 6, 7 };
	//std::vector<int> res = { 0, 3, 3, 3, 4, 4, 0};

	ofs.write((const char*)&num12, sizeof(int));
	ofs.write((const char*)&num22, sizeof(int));
	//
	char f1[11] = "first.dat";
	char f2[11] = "second.dat";
	char f3[11] = "third.dat";

	ofs.write((const char*)&f1, strlen(f1) + 1);
	ofs.write((const char*)&f2, strlen(f2) + 1);
	ofs.write((const char*)&f3, strlen(f3) + 1);

	//for (int i = 0; i < strs.size(); i++)
		//ofs.write((const char*)&strs[i], strlen(strs[i]));

	//ofs.write((const char*)args.data(), args.size() * sizeof(int));

	//ofs.write((const char*)(args.data()), args.size() * sizeof(int));
	//ofs.write((const char*)(res.data()), res.size() * sizeof(int));

	ofs.close();

	/*for (int arg = smallerNum; arg <= biggerNum; arg++)
	{*/
	//read
	int arg = 7;
		std::ifstream ifs("func.dat", std::ios::binary);
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

			if (!func.isDefined(arg))
			{
				try {
					func.operator()(arg);
				}
				catch (const std::invalid_argument& exc) {
					std::cout << exc.what();
				}
			}
			else
				std::cout << func.operator()(arg).result;

			break;
		}
		case 1:
		{
			std::vector<int> vectorOfNums(elementCount);
			ifs.read((char*)vectorOfNums.data(), vectorOfNums.size() * sizeof(int));
			CriteriaT1 func(vectorOfNums);

			if (!func.isDefined(arg))
			{
				try {
					func.operator()(arg);
				}
				catch (const std::invalid_argument& exc) {
					std::cout << exc.what();
				}
			}
			else
				std::cout << func.operator()(arg);

				break;
			}
			case 2:
			{
				std::vector<int> vectorOfNums(elementCount);
				ifs.read((char*)vectorOfNums.data(), vectorOfNums.size() * sizeof(int));

				CriteriaT2 func(vectorOfNums);

				if (!func.isDefined(arg))
				{
					try {
						func.operator()(arg);
					}
					catch (const std::invalid_argument& exc) {
						std::cout << exc.what();
					}
				}
				else
					std::cout << func.operator()(arg);

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

				if (!func.isDefined(arg))
				{
					try {
						func.operator()(arg);
					}
					catch (const std::invalid_argument& exc) {
						std::cout << exc.what();
					}
				}
				else
					std::cout << func.operator()(arg);

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

				if (!func.isDefined(arg))
				{
					try {
						func.operator()(arg);
					}
					catch (const std::invalid_argument& exc) {
						std::cout << exc.what();
					}
				}
				else
					std::cout << func.operator()(arg);

				break;
			}
			}
	//}
}