#include "Unique_ptr.h"
#include "TestUnique_ptr.h"
#include "Move.h"

#include<cassert>

void TestUnique_ptr::allTests()
{
	testConstructors();
	testMoveAssignmentOperator();
	testOperators();
	testCompareOperators();
	testMakeUnique();
	testReset();
}
void TestUnique_ptr::testConstructors()
{
	unique_ptr<int> testUnique_ptr1 = unique_ptr<int>(new int(5));
	assert(*testUnique_ptr1 == 5);

	unique_ptr<int> testUnique_ptr2 = unique_ptr<int>(new int(10));
	unique_ptr<int> testUnique_ptr3 = unique_ptr<int>(move(testUnique_ptr2));
	assert(*testUnique_ptr3 == 10);
	assert(testUnique_ptr2.isFree() == true);
}
void TestUnique_ptr::testMoveAssignmentOperator()
{
	unique_ptr<int> testUnique_ptr1 = unique_ptr<int>(new int(10));
	assert(*testUnique_ptr1 == 10);
	unique_ptr<int> testUnique_ptr2 = unique_ptr<int>(new int(20));
	assert(*testUnique_ptr2 == 20);
	testUnique_ptr1 = unique_ptr<int>(move(testUnique_ptr2));
	assert(*testUnique_ptr1 == 20);
	assert(testUnique_ptr2.isFree() == true);
}
void TestUnique_ptr::testOperators()
{
	int* testInt = new int(10);
	unique_ptr<int> testUnique_ptr1 = unique_ptr<int>(testInt);
	assert(*testUnique_ptr1 == 10);

	auto testUnique_ptr2 = unique_ptr<int[]>(new int[10]);
	for (int i = 0; i < 10; i++)
	{
		testUnique_ptr2[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		assert(testUnique_ptr2[i] == i);
	}
}
void TestUnique_ptr::testCompareOperators()
{
	int array[10]{};
	for (int i = 0; i < 10; i++)
	{
		array[i] = i;
	}
	unique_ptr<int> testUnique_ptr1 = unique_ptr<int>(array + 3);
	unique_ptr<int> testUnique_ptr2 = unique_ptr<int>(array + 3);
	unique_ptr<int> testUnique_ptr3 = unique_ptr<int>(array + 5);
	unique_ptr<int> testUnique_ptr4 = unique_ptr<int>();
	assert(testUnique_ptr4 == nullptr);
	assert(testUnique_ptr1 == testUnique_ptr2);
	assert(testUnique_ptr1 != testUnique_ptr3);
	assert(testUnique_ptr4 == nullptr);
	assert(nullptr == testUnique_ptr4);
	assert(testUnique_ptr1 != nullptr);
	assert(nullptr != testUnique_ptr1);
	testUnique_ptr1.release();
	testUnique_ptr2.release();
	testUnique_ptr3.release();
	testUnique_ptr4.release();
}
void TestUnique_ptr::testMakeUnique()
{
	unique_ptr<int> testUnique_ptr1 = make_unique<int>(20);
	assert(*testUnique_ptr1 == 20);
}
void TestUnique_ptr::testReset()
{
	int* testInt = new int(20);
	unique_ptr<int> testUnique_ptr = unique_ptr<int>(testInt);
	assert(*testUnique_ptr == 20);
	testUnique_ptr.reset();
	assert(testUnique_ptr.isFree() == true);
}
