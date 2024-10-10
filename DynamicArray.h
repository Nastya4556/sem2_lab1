#pragma once
#include "Unique_ptr.h"
#include "Swap.h"
#include "Shared_ptr.h"

#include <stdexcept>

template <class T> class DynamicArray
{
private:
	int size = 0;
	unique_ptr<T[]> array;
	void swap(DynamicArray<T>& other)
	{
		my_swap(size, other.size);
		my_swap(array, other.array);
	}
public:
	DynamicArray() :size(0), array(nullptr) {};
	DynamicArray(int size):size(size)
	{
		if (size < 0) 
			throw std::out_of_range("Invalid size\n");
		if (size > 0)
		{
			array = unique_ptr<T[]>(new T[size]);
		}
	}
	DynamicArray(const T* other, int size) : DynamicArray<T>(size)
	{
		if (other == nullptr) throw std::out_of_range("Invalid argument in constructor");
		for (int i = 0; i < size; i++)
		{
			array[i] = other[i];
		}
	}
	DynamicArray(const unique_ptr<T[]>& other, int size) : DynamicArray<T>(size)
	{
		if (other == nullptr) 
			throw std::out_of_range("Invalid argument in constructor");
		for (int i = 0; i < size; i++)
		{
			array[i] = other[i];
		}
	}
	virtual ~DynamicArray() = default;
	T& operator[](int index)
	{
		if (index < 0 || index >= this->size) 
			throw std::out_of_range("Index is invalid");
		return array[index];
	}
	const T& operator[](int index) const
	{
		if (size <= index || size <= 0)
			throw std::out_of_range("invalid size\n");
		return array[index];
	}
	T get(int index)
	{
		if (index < 0 || index >= this->size) 
			throw std::out_of_range("Index out of range\n");
		return array[index];
	}
	int getSize()
	{
		if (size < 0) 
			throw std::out_of_range("Invalid size\n");
		return this->size;
	}
	void set(int index, const T& value)
	{
		if (index < 0 || index > this->size) 
			throw std::out_of_range("Index out of range\n");
		this->array[index] = value;
	}
	void resize(int newSize)
	{
		if (newSize < 0 || size > newSize) 
			throw std::out_of_range("Invalid size");
		if (newSize == 0)
		{
			array.reset();
			return;
		}
		auto buf = unique_ptr<T[]>(new T[newSize]);
		int minimum{};
		if (size < newSize)
		{
			minimum = size;
		}
		else
		{
			minimum = newSize;
		}
		if (array != nullptr)
		{
			for (int i = 0; i < minimum; i++)
			{
				buf[i] = array[i];
			}
		}
		array = buf;
		size = newSize;
	}
	void append(const T& value)
	{
		this->resize(this->getSize() + 1);
		array[size - 1] = value;
	}
	DynamicArray<T>& operator =(DynamicArray<T> other)
	{
		swap(other);
		return *this;
	}
};