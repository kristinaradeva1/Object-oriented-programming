#pragma once
#include "PartialFunction.h"
class PartialFunctionCollection : public PartialFunction
{
protected:
	PartialFunction** partialFuncs = nullptr;
	size_t partialFuncsCount = 0;
	size_t capacity = 0;
private:
	size_t dataToAllocBySize(size_t partialFuncsCount) const;
	void free();
	void copyFrom(const PartialFunctionCollection& other);
	void moveFrom(PartialFunctionCollection&& other);
	void resize(size_t newSize);
public:
	PartialFunctionCollection();
	PartialFunctionCollection(const PartialFunction* const* partialFuncs, size_t partialFuncsCount);

	PartialFunctionCollection(const PartialFunctionCollection& other);
	PartialFunctionCollection& operator=(const PartialFunctionCollection& other);

	PartialFunctionCollection(PartialFunctionCollection&& other) noexcept;
	PartialFunctionCollection& operator=(PartialFunctionCollection&& other) noexcept;

	~PartialFunctionCollection();

	size_t getSize() const;
	size_t getCapacity() const;

	//virtual int operator()(int argument) const = 0;
	//virtual bool isDefined(int argument) const = 0;
	//virtual PartialFunction* clone() const = 0
};