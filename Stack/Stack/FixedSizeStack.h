#pragma once

///
///	Проста реализация на стек с фиксиран размер
///
/// Реализацията заделя динамично масив за елементите на стека,
/// но размерът му не може да се променя.
///
class FixedSizeStack {
public:
	FixedSizeStack(size_t Size);
	~FixedSizeStack();
	FixedSizeStack(FixedSizeStack const & Other);
	FixedSizeStack& operator=(FixedSizeStack const & Other);

public:
	bool Push(double element);
	bool Pop(double& element);
	double Peek() const;
	void RemoveAll();

	size_t GetAllocatedSize() const;
	size_t GetSize() const;
	bool IsEmpty() const;

private:
	void Init();
	void Destroy();
	void CopyFrom(FixedSizeStack const & Other);

private:
	double* pData;
	size_t Allocated;
	size_t Used;
};