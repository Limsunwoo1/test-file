#pragma once
#include <stdlib.h>

template<typename T>
class CArray
{
	T* Data;
	int CurCount;
	int TotalCount;
public:
	CArray();
	~CArray();

	// 원소를 뒤에서 추가한다.
	void PushBack(T value);

	T operator[] (int index);

	int GetSize() {return CurCount;}
	void SetCount(int InCount) {CurCount = InCount;}
};

template<typename T>
CArray<T>::CArray()
	: Data(nullptr)
	, CurCount(0)
	, TotalCount(1)
{
	Data = (T*)malloc(TotalCount * sizeof(T));
}

template<typename T>
CArray<T>::~CArray()
{
	/*if (Data)
		delete[] Data;*/
}

template<typename T>
void CArray<T>::PushBack(T value)
{
	if (CurCount == TotalCount)
	{
		TotalCount *= 2;
		Data = (T*)realloc(Data, TotalCount * sizeof(T));
	}
	Data[CurCount++] = value;
}

template<typename T>
T CArray<T>::operator[] (int index)
{
	return Data[index];
}