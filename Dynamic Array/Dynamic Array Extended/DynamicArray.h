#pragma once

class DynamicArrayElementProxy;

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
	void SetAt(size_t, int);

	void Print() const;

public:
	DynamicArray operator+(DynamicArray const &) const;
	DynamicArrayElementProxy operator[](size_t);
	const DynamicArrayElementProxy operator[](size_t) const;

private:
	void Reallocate(size_t NewSize);
	void CopyFrom(DynamicArray const &);
};


///
/// Представя елемент в динамичен масив
///
class DynamicArrayElementProxy
{
private:
	/// Указател към динамичния масив, който е създал proxy-то
	DynamicArray *pParent;

	/// Индекс на елемента на динамичния масив, който proxy-то представя
	size_t ParentElementIndex;
	
public:
	DynamicArrayElementProxy(DynamicArray *, size_t);

public:
	operator int() const;
	
	DynamicArrayElementProxy& operator=(int);
};