#include "DynamicArray.h"
#include "TestDynamicArray.h"
#include "Unique_ptr.h"

#include <cassert>

void TestDynamicArray::allTests()
{
	testConstructors();
	testGet();
	testGetSize();
	testSet();
}
void TestDynamicArray::testConstructors()
{
	DynamicArray<int> testArray1;
	assert(testArray1.getSize() == 0);

	int a[6] = { 1, 2, 3, 4, 5, 6 };
	int length = 6;
	DynamicArray<int> testArray2(a, length);
	assert(testArray2.getSize() == length);
	for (int i = 0; i < length; i++)
	{
		assert(testArray2.get(i) == a[i]);
	}

	DynamicArray<int> testArray3(length);
	assert(testArray3.getSize() == length);

	int size = 5;
	auto testUnique_ptr = unique_ptr<int[]>(new int[5]);
	for (int i = 0; i < size; i++)
	{
		testUnique_ptr[i] = i;
	}
	DynamicArray<int> testArray4(testUnique_ptr, size);
	assert(testArray4.getSize() == 5);
	for (int i = 0; i < size; i++)
	{
		assert(testArray4[i] == i);
	}

}
void TestDynamicArray::testGet()
{
	int a[6] = { 1, 2, 3, 4, 5, 6 };
	int length = 6;
	DynamicArray<int> testArray(a, length);
	for (int i = 0; i < length; i++)
	{
		assert(testArray.get(i) == a[i]);
	}
}
void TestDynamicArray::testGetSize()
{
	int a[6] = { 1, 2, 3, 4, 5, 6 };
	int length = 6;
	DynamicArray<int> testArray(a, length);
	assert(testArray.getSize() == length);
}
void TestDynamicArray::testSet()
{
	int a[6] = { 1,2, 3, 4, 5, 6 };
	int length = 6;
	int index = 2;
	int value = 50;
	DynamicArray<int> testArray(a, length);
	testArray.set(index, value);
	assert(testArray.getSize() == length);
	assert(testArray.get(index) == value);
}
