#pragma once

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

	virtual void PrintInfo() = 0;

protected:
	HashingFunction* pHashingFunction;
};
