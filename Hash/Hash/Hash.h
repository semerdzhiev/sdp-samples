/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <iostream>

///
///	Represents a hashing function
///	
class HashingFunction
{
public:
    virtual ~HashingFunction() = default;

	/// Calculates the hash of an int
	virtual int CalculateHash(int Value) = 0;
};


///
///	A modular hashing function
///
/// The hash for a specific value V is calculated as V % Mod
///
class ModularHashingFunction : public HashingFunction
{
private:
	int Mod;

public:
	ModularHashingFunction(int Mod)
        : Mod(Mod)
	{
        // Nothing to do here
	}

	int CalculateHash(int Value) override
	{
		return Value % Mod;
	}
};


///
/// A hashing function, which tries not to cluster the hash values
///
/// The hash for a specific value V is calculated as (V % Mod) * Multiplier
///
class ModAndMultiplyHashingFunction : public HashingFunction
{
private:
    int Mod;
    int Multiplier;

public:
    ModAndMultiplyHashingFunction(int Mod, int Multiplier)
        : Mod(Mod), Multiplier(Multiplier)
    {
        // Nothing to do here
    }
    
    int CalculateHash(int Value) override
    {
        return (Value % Mod) * Multiplier;
    }
};


///
///	Parent class for all hashes
///
class Hash
{
protected:
	HashingFunction * pHashingFunction;

public:
	Hash(HashingFunction* pHashingFunction = nullptr)
        : pHashingFunction(pHashingFunction)
	{
		// Nothing to do here
	}

    virtual ~Hash() = default;

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
};
