#pragma once

#include <list>

#include "Hash.h"

class NotReallyHash : public Hash
{
public:
	virtual bool Add(const int Value);
	virtual bool Search(const int Value);
	virtual void PrintInfo() const;

private:
	std::list<int> Data;
};

