#include "Multiset.h"
unsigned length(int number)
{
	unsigned lngth = 0;
	while (number != 0)
	{
		number /= 10;
		lngth++;
	}
	return lngth;
}

int min(int num1, int num2)
{
	return num1 < num2 ? num1 : num2;
}

int power(int base, unsigned int exponent) {
	if (exponent == 0) 
		return 1;

	int result = 1;

	for (unsigned int i = 0; i < exponent; ++i) {
		result *= base;
	}

	return result;
}

unsigned int fromBinaryToDecimal(unsigned int number)
{
	unsigned int result = 0;
	unsigned int mult = 1;
	while (number != 0)
	{
		result += ((number % 10) * mult);
		mult *= 2;
		number /= 10;
	}
	return result;
}

unsigned int toBinaryFromDecimal(unsigned int number)
{
	int result = 0;
	int mult = 1;
	while (number != 0)
	{
		if (number % 2 == 1)
			result += mult;
		mult *= 10;
		number /= 2;
	}
	return result;
}

unsigned power(unsigned base, unsigned exponent)
{
	return 0;
}

//DynamicSet IntersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs)
//{
//	return DynamicSet();
//}

void MultiSet::free()
{
	delete[] buckets;
	biggestNum = 0;
	kBits = 1;
	buckets = nullptr;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	this->bucketCount = other.bucketCount;
	this->buckets = new uint8_t[other.bucketCount];
	for (int i = 0; i < bucketCount; i++) {
		this->buckets[i] = other.buckets[i];
	}
	this->biggestNum = other.biggestNum;
	this->kBits = other.kBits;
}

unsigned MultiSet::getBucketIndex(unsigned number) const
{
	//a number can be in two buckets at the same time
	if (number <= biggestNum) 
	{
		return (number * kBits) / bitsInBucket;
	}
	else
	{
		return 0;
	}
}

unsigned MultiSet::getFirstBitIndexWithDifferentIndexation(unsigned number) const
{
	if (number <= biggestNum)
	{
		return number * kBits;
	}
	else
	{
		return 0;
	}
}
unsigned MultiSet::getFirstBitIndex(unsigned number) const
{
	unsigned bucketIdx = getBucketIndex(number);
	if (number <= biggestNum)
	{
		return number * kBits - bucketIdx * bitsInBucket;
	}
	else
	{
		return 0;
	}
}

unsigned MultiSet::getBucketIndexByBitIndex(unsigned bitIndex) const
{
	if (bitIndex <= bitsInBucket * bucketCount)
	{
		return bitIndex / bitsInBucket;

	}
	else
	{
		return 0;
	}
}

unsigned MultiSet::getLastBitOfBucket(unsigned bucketIndex) const
{
	if (bucketIndex < bucketCount) 
	{
		unsigned lastBitOfBucket = 0;
		for (int i = 0; i <= bucketIndex; i++) {
			lastBitOfBucket += bitsInBucket;
		}
		return lastBitOfBucket - 1;
	}
	else
	{
		return 0;
	}
}

bool MultiSet::isNumberOnlyInOneBucket(unsigned number) const
{
	unsigned bucketIdx = getBucketIndex(number);
	unsigned firstBitIdx = getFirstBitIndexWithDifferentIndexation(number);
	unsigned lastBitIdx = firstBitIdx + kBits - 1;

	unsigned lastBitOfBucketIdx = getLastBitOfBucket(bucketIdx);

	if (lastBitIdx > lastBitOfBucketIdx)
	{
		return false;
	} 
	else
	{
		return true;
	}
}

unsigned MultiSet::getBiggestNumThatOccurs() const
{
	for (int i = biggestNum; i >= 0; i--)
	{
		if (countOccurrences(i))
		{
			return i;
		}
	}
}

unsigned MultiSet::getSmallestNumThatOccurs() const
{
	for (int i = 0; i <= biggestNum; i++)
	{
		if (countOccurrences(i))
		{
			return i;
		}
	}
}

MultiSet::MultiSet(unsigned biggestNum, unsigned short kBits)
{
	setBiggestNum(biggestNum);
	setkBits(kBits);
	//numbersInBucket = (bitsInBucket / kBits);
	bucketCount = (kBits * biggestNum) / bitsInBucket + 1;
	buckets = new uint8_t[bucketCount];
	for (int i = 0; i < bucketCount; i++) {
		buckets[i] = 0;
	} 
}

MultiSet::~MultiSet()
{
	free();
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

void MultiSet::setBiggestNum(unsigned biggestNum)
{
	if (biggestNum >= 0) {
		this->biggestNum = biggestNum;
	}
	else {
		this->biggestNum = 0;
	}
}

void MultiSet::setkBits(unsigned short kBits)
{
	if (kBits >= 1 && kBits <= 8) {
		this->kBits = kBits;
	} 
	else {
		this->kBits = 1;
	}
}

void MultiSet::setBuckets(const uint8_t* buckets, unsigned bucketCount)
{
	if (!buckets)
		return;

	this->buckets = new uint8_t[bucketCount];
	for (int i = 0; i < bucketCount; i++)
		this->buckets[i] = buckets[i];
}

bool MultiSet::isBitUp(unsigned bucketIndex, unsigned bitIndex) const
{
	if (bucketIndex < bucketCount)
	{
		uint8_t mask = 1 << bitIndex;

		return (buckets[bucketIndex] & mask);
	}
	else
	{
		return 0;
	}
	
}

void MultiSet::liftBit(unsigned bucketIndex, unsigned bitIdx)
{
	if (!isBitUp(bucketIndex, bitIdx))
	{
		uint8_t mask = 1 << bitIdx;
		buckets[bucketIndex] |= mask;
	}
	else
	{
		return;
	}
}

void MultiSet::dropBit(unsigned bucketIndex, unsigned bitIdx)
{
	if (isBitUp(bucketIndex, bitIdx))
	{
		uint8_t mask = 1 << bitIdx;
		mask = ~mask;
		buckets[bucketIndex] &= mask;
	}
	else
	{
		return;
	}
}

unsigned MultiSet::countOccurrences(unsigned number) const
{
	unsigned occurrencesInBinary = 0;
	unsigned temp = 1;
	if (isNumberOnlyInOneBucket(number))
	{
		unsigned bucketIdx = getBucketIndex(number);
		unsigned firstBitIdx = getFirstBitIndex(number);
		unsigned lastBitIdx = firstBitIdx + kBits - 1;

		for (int i = lastBitIdx; i >= firstBitIdx; i--)
		{
			unsigned curBit = isBitUp(bucketIdx, i);
			curBit *= temp;
			occurrencesInBinary += curBit;
			temp *= 10;

			if (i == 0)
				break;
		}
	}
	else
	{
		unsigned firstBitIdx = getFirstBitIndexWithDifferentIndexation(number);
		unsigned lastBitIdx = firstBitIdx + kBits - 1;

		for (int bit = lastBitIdx; bit >= firstBitIdx; bit--)
		{
			unsigned currentBucketIdx = getBucketIndexByBitIndex(bit);
			unsigned curBitInBucket = bit - currentBucketIdx * bitsInBucket;

			unsigned curBit = isBitUp(currentBucketIdx, curBitInBucket);
			curBit *= temp;
			occurrencesInBinary += curBit;
			temp *= 10;
		}
	}
	return fromBinaryToDecimal(occurrencesInBinary);
}

void MultiSet::add(unsigned number)
{
	if (number > biggestNum)
		return;  
		
	if (isNumberOnlyInOneBucket(number)) {
		unsigned occurrences = countOccurrences(number);
		unsigned bucketIdx = getBucketIndex(number);
		unsigned firstBitIdx = getFirstBitIndex(number);
		unsigned lastBitIdx = firstBitIdx + kBits - 1;

		if (occurrences < (power(2, kBits) - 1))
		{
			occurrences++;
			unsigned occurrencesInBinary = toBinaryFromDecimal(occurrences);

			for (int bit = lastBitIdx; bit >= firstBitIdx; bit--)
			{
				unsigned curBit = isBitUp(bucketIdx, bit);
				unsigned curDigit = occurrencesInBinary % 10;

				if (curBit == 0 && curDigit == 1)
				{
					liftBit(bucketIdx, bit);
				}
				else if (curBit == 1 && curDigit == 0)
				{
					dropBit(bucketIdx, bit);
				}
				occurrencesInBinary /= 10;
				if (bit == 0)
					break;
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		unsigned occurrences = countOccurrences(number);
		unsigned firstBitIdx = getFirstBitIndexWithDifferentIndexation(number);
		unsigned lastBitIdx = firstBitIdx + kBits - 1;

		if (occurrences < (power(2, kBits) - 1))
		{
			occurrences++;
			unsigned occurrencesInBinary = toBinaryFromDecimal(occurrences);

			for (int bit = lastBitIdx; bit >= firstBitIdx; bit--)
			{
				unsigned currentBucketIdx = getBucketIndexByBitIndex(bit);
				unsigned curBitInBucket = bit - currentBucketIdx * bitsInBucket;

				unsigned curBit = isBitUp(currentBucketIdx, curBitInBucket);
				unsigned curDigit = occurrencesInBinary % 10;


				if (curBit == 0 && curDigit == 1)
				{
					liftBit(currentBucketIdx, curBitInBucket);
				}
				else if (curBit == 1 && curDigit == 0)
				{
					dropBit(currentBucketIdx, curBitInBucket);
				}
				occurrencesInBinary /= 10;
				if (bit == 0)
					break;
			}
		}
		else
		{
			return;
		}
	}
}

void MultiSet::print() const
{
	std::cout << "{ ";
	for (int currentNumber = 0; currentNumber <= biggestNum; currentNumber++) {
		unsigned occurrences = countOccurrences(currentNumber);
		if (occurrences == 0)
			continue;
		unsigned smallest = getSmallestNumThatOccurs();
		unsigned biggest = getBiggestNumThatOccurs();
		for (int i = 0; i < occurrences; i++)
		{
			if (currentNumber == smallest && i == 0)
			{
				std::cout << currentNumber;
			}
			else
			{
				std::cout << ", " << currentNumber;
			}
		}	
	}
	std::cout << " }" << std::endl;
}

MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs)
{
	MultiSet result(min(lhs.biggestNum, rhs.biggestNum), min(lhs.kBits, rhs.kBits));
	for (int cur = 0; cur <= result.biggestNum; cur++)
	{
		unsigned minOccurrences = min(lhs.countOccurrences(cur), rhs.countOccurrences(cur));
		for (int i = 0; i < minOccurrences; i++)
		{
			result.add(cur);
		}
	}
	return result;
}

MultiSet DifferenceOfSets(const MultiSet& lhs, const MultiSet& rhs)
{
	unsigned biggestOcc = 0;
	unsigned biggestNumber = 0;
	for (int cur = 0; cur <= lhs.biggestNum; cur++)
	{
		unsigned lhsOcc = lhs.countOccurrences(cur);
		unsigned rhsOcc = rhs.countOccurrences(cur);
		if (lhsOcc > rhsOcc)
		{
			unsigned curOcc = lhsOcc - rhsOcc;
			if (curOcc > biggestOcc)
				biggestOcc = curOcc;

			if (cur > biggestNumber)
				biggestNumber = cur;
		}
	}
	unsigned biggestOccInBinary = toBinaryFromDecimal(biggestOcc);
	unsigned bitsOfOcc = length(biggestOccInBinary);
	MultiSet result(biggestNumber, bitsOfOcc);

	for (int cur = 0; cur <= biggestNumber; cur++)
	{
		unsigned lhsOcc = lhs.countOccurrences(cur);
		unsigned rhsOcc = rhs.countOccurrences(cur);
		if (lhsOcc > rhsOcc)
		{
			unsigned curOcc = lhsOcc - rhsOcc;
			for (int i = 0; i < curOcc; i++)
			{
				result.add(cur);
			}
		}
	}
	return result;
}

MultiSet AdditionOfSet(const MultiSet& set)
{
	unsigned maxOcc = power(2, set.kBits) - 1;
	unsigned maxOccInBinary = toBinaryFromDecimal(maxOcc);
	unsigned bitsOfOcc = length(maxOccInBinary);

	unsigned biggestNumber = 0;
	for (int cur = set.biggestNum; cur >= 0; cur--)
	{
		unsigned curOcc = set.countOccurrences(cur);
		unsigned newOcc = 0;
		if (curOcc < maxOcc)
		{
			biggestNumber = cur;
			break;
		}
	}

	MultiSet result(biggestNumber, bitsOfOcc);

	for (int cur = 0; cur <= biggestNumber; cur++)
	{
		unsigned curOcc = set.countOccurrences(cur);
		unsigned newOcc = 0;
		if (curOcc < maxOcc)
		{
			newOcc = maxOcc - curOcc;
		}
		for (int i = 0; i < newOcc; i++)
		{
			result.add(cur);
		}
	}
	return result;
}

void MultiSet::printAsInMemory() const
{
	std::cout << "| ";
	for (int i = bucketCount - 1; i >= 0; i--)
	{
		for (int bit = 0; bit < 8; bit++)
		{
			unsigned currentBucketIdx = getBucketIndexByBitIndex(bit);

			unsigned curBit = isBitUp(i, bit);
			if (bit == 0 && i == bucketCount - 1)
				std::cout << "| " << curBit;
			else
				std::cout << " | " << curBit;
		}
		std::cout << " |";
	}
	std::cout << " |" << std::endl;
}

const uint8_t* MultiSet::getBuckets() const
{
	return buckets;
}

unsigned short MultiSet::getKBits() const
{
	return kBits;
}

unsigned MultiSet::getBucketCount() const
{
	return bucketCount;
}

unsigned MultiSet::getBiggestNum() const
{
	return biggestNum;
}

void writeToBinary(std::ofstream& ofs, const MultiSet& multiset)
{
	unsigned kBits = multiset.getKBits();
	ofs.write((const char*)&kBits, sizeof(kBits));
	unsigned biggestNum = multiset.getBiggestNum();
	ofs.write((const char*)&biggestNum, sizeof(biggestNum));
	unsigned sizeOfBuckets = multiset.getBucketCount() * sizeof(multiset.getBuckets()[0]);
	ofs.write((const char*)multiset.getBuckets(), sizeOfBuckets);
}

void readFromBinary(std::ifstream& ifs, MultiSet& multiset)
{
	unsigned kBits;
	unsigned biggestNum;
	ifs.read((char*)&kBits, sizeof(kBits));
	ifs.read((char*)&biggestNum, sizeof(biggestNum));
	unsigned bucketCount = kBits * (biggestNum + 1) / bitsInBucket;
	uint8_t* buckets = new uint8_t[bucketCount];
	ifs.read((char*)buckets, bucketCount * sizeof(buckets[0]));

	multiset.setkBits(kBits);
	multiset.setBiggestNum(biggestNum);
	multiset.setBuckets(buckets, bucketCount);
}