#include "PartialFunctionCollection.h"
#include <iostream>

static unsigned roundToPowerOfTwo(unsigned v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

static size_t max(size_t num1, size_t num2)
{
	return num1 > num2 ? num1 : num2;
}

size_t PartialFunctionCollection::dataToAllocBySize(size_t partialFuncsCount) const
{
	return max(roundToPowerOfTwo(partialFuncsCount), 16u);
}

void PartialFunctionCollection::free()
{
	for (int i = 0; i < partialFuncsCount; i++)
	{
		delete partialFuncs[i];
	}
	delete[] partialFuncs;
}

void PartialFunctionCollection::copyFrom(const PartialFunctionCollection& other)
{
	this->partialFuncs = new PartialFunction * [other.capacity];
	this->partialFuncsCount = other.partialFuncsCount;
	this->capacity = other.capacity;

	for (int i = 0; i < partialFuncsCount; i++)
	{
		PartialFunction* cloned = other.partialFuncs[i]->clone();
		if (cloned)
			this->partialFuncs[i] = cloned; //warning ima
	}
}

void PartialFunctionCollection::moveFrom(PartialFunctionCollection&& other)
{
	this->partialFuncsCount = other.partialFuncsCount;
	other.partialFuncs = 0;

	this->capacity = other.capacity;
	other.capacity = 0;

	this->partialFuncs = other.partialFuncs;
	other.partialFuncs = 0;
}

void PartialFunctionCollection::resize(size_t newSize)
{
	if (newSize <= partialFuncsCount)
		return;

	capacity = dataToAllocBySize(newSize);
	PartialFunction** newCollection = new PartialFunction * [capacity];
	for (int i = 0; i < partialFuncsCount; i++)
	{
		newCollection[i] = partialFuncs[i];
	}
	delete[] partialFuncs;
	partialFuncs = newCollection;
}

PartialFunctionCollection::PartialFunctionCollection()
{
	capacity = 8;
	partialFuncs = new PartialFunction * [capacity] {nullptr};
	partialFuncsCount = 0;
}

PartialFunctionCollection::PartialFunctionCollection(const PartialFunction* const* partialFuncs, size_t _partialFuncsCount) : partialFuncsCount(_partialFuncsCount)
{
	capacity = dataToAllocBySize(partialFuncsCount);
	this->partialFuncs = new PartialFunction * [capacity];
	for (int i = 0; i < partialFuncsCount; i++)
	{
		PartialFunction* cloned = partialFuncs[i]->clone();
		if (cloned)
			this->partialFuncs[i] = cloned; //warning
	}
}

PartialFunctionCollection::PartialFunctionCollection(const PartialFunctionCollection& other)
{
	copyFrom(other);
}

PartialFunctionCollection& PartialFunctionCollection::operator=(const PartialFunctionCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

PartialFunctionCollection::PartialFunctionCollection(PartialFunctionCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

PartialFunctionCollection& PartialFunctionCollection::operator=(PartialFunctionCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

PartialFunctionCollection::~PartialFunctionCollection()
{
	free();
}

size_t PartialFunctionCollection::getSize() const
{
	return partialFuncsCount;
}

size_t PartialFunctionCollection::getCapacity() const
{
	return capacity;
}
