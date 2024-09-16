#pragma once
#include <iostream>
#include <fstream>

constexpr unsigned bitsInBucket = sizeof(uint8_t) * 8;
class MultiSet 
{
	uint8_t* buckets = nullptr;
    unsigned biggestNum = 0;
	unsigned short kBits = 1;

	//unsigned numbersInBucket;
	unsigned bucketCount = 0;
	
	void free();
	void copyFrom(const MultiSet& other);

	unsigned getBucketIndex(unsigned number) const;
	unsigned getBucketIndexByBitIndex(unsigned bitIndex) const;
	unsigned getFirstBitIndex(unsigned number) const;
	unsigned getFirstBitIndexWithDifferentIndexation(unsigned number) const;

	unsigned getLastBitOfBucket(unsigned bucketIndex) const;
	bool isNumberOnlyInOneBucket(unsigned number) const;

	unsigned getBiggestNumThatOccurs() const;
	unsigned getSmallestNumThatOccurs() const;

	bool isBitUp(unsigned bucketIndex, unsigned boxIndex) const;
	void liftBit(unsigned bucketIndex, unsigned bitIdx);
	void dropBit(unsigned bucketIndex, unsigned bitIdx);

public: 
	MultiSet() = default;
	MultiSet(unsigned biggestNum, unsigned short kBits);
	~MultiSet();
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);

	void setBiggestNum(unsigned biggestNum);
	void setkBits(unsigned short kBits);
	void setBuckets(const uint8_t* buckets, unsigned bucketCount);

	unsigned getBiggestNum() const;
	const uint8_t* getBuckets() const;
	unsigned short getKBits() const;
	unsigned getBucketCount() const;

	void add(unsigned number);
	unsigned countOccurrences(unsigned number) const;

	void print() const;
	void printAsInMemory() const;

	friend MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs); 
	friend MultiSet DifferenceOfSets(const MultiSet& lhs, const MultiSet& rhs); 
	friend MultiSet AdditionOfSet(const MultiSet& set); 
}; 

unsigned int fromBinaryToDecimal(unsigned int n);
unsigned int toBinaryFromDecimal(unsigned int n);
int power(int base, unsigned int exponent); //only works with an unsigned exponent
int min(int num1, int num2);
unsigned length(int number);

void writeToBinary(std::ofstream& ofs, const MultiSet& multiset);
void readFromBinary(std::ifstream& ifs, MultiSet& multiset);