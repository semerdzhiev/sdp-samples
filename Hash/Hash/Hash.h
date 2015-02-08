#pragma once

#include <iostream>

///
///	Represents a hashing function
///	
class HashingFunction
{
public:
	virtual ~HashingFunction()
	{
	}

	/// Calculates the hash of an int
	virtual int CalculateHash(int Value) = 0;
};


///
///	A modular hashing function
///
class ModularHashingFunction : public HashingFunction
{
public:
	ModularHashingFunction(int Mod)
	{
		this-> Mod = Mod;
	}

	virtual int CalculateHash(int Value)
	{
		/*
		int result = 1;

		while (Value)
		{
			result = ((result << 4) | (Value & 0xF)) % Mod;
			Value >>= 4;
		}

		return result;
		*/
		
		return Value % Mod;
	}

private:
	int Mod;
};


///
///	Parent class for all hashes
///
class Hash
{
public:
	Hash(HashingFunction* pHashingFunction = 0)
	{
		this->pHashingFunction = pHashingFunction;
	}

	virtual ~Hash()
	{
	}

	virtual bool Add(const int Value) = 0;
	
	virtual bool Search(const int Value) = 0;

	virtual void PrintInfo() const = 0;

	void PrintCommonInfo(size_t ElementsCount, size_t MemoryUsed) const
	{
		size_t elementsSize = ElementsCount * sizeof(int);

		size_t data = (elementsSize * 100) / MemoryUsed;
		
		std::cout
			<< "\n   - Stored elements: " << ElementsCount
			<< "\n   - Space required for elements: " << ElementsCount << " x sizeof(int) = " << elementsSize << " bytes"
			<< "\n   - Memory used: " << MemoryUsed << " byte(s) (~ " << (MemoryUsed / ElementsCount) << " bytes per element)"
			<< "\n   - Data vs Representation: " << data << "% data, " << (100 - data) << "% representation"
			<< std::endl << std::endl;
	}

protected:
	HashingFunction* pHashingFunction;
};
