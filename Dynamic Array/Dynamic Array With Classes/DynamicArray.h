#pragma once

///
/// Представя динамичен масив
///
class DynamicArray
{
private:
	/// Данните на масива
	int *pData;

	/// Размер на заделената памет за масива
	size_t AllocatedSize;
	
	/// Брой на използваните клетки от масива
	size_t Length;

public:
	DynamicArray();
	DynamicArray(DynamicArray const &);
	DynamicArray& operator=(DynamicArray const &);
	~DynamicArray();

public:
	void Free();
	
	void Add(int Element);

	size_t GetAllocatedSize() const;
	size_t GetLength() const;
	int GetAt(size_t) const;

	void Print() const;

public:
	DynamicArray operator+(DynamicArray const &) const;

private:
	void Reallocate(size_t NewSize);
	void CopyFrom(DynamicArray const &);
};