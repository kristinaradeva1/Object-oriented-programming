#pragma once
template<class T>
class Pair
{
public:
	T argument;
	int result;

	Pair() : Pair(0, 0) {}
	Pair(int _argument, int _result) : argument(_argument), result(_result) {}
};