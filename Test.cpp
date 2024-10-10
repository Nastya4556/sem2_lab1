#include "Test.h"
#include "TestUnique_ptr.h"
#include "TestShared_ptr.h"
#include "TestDynamicArray.h"

void Test::allTests()
{
	testUnique_ptr();
	testShared_ptr();
	testDynamicArray();
}
void Test::testUnique_ptr()
{
	TestUnique_ptr testUnique_ptr;
	testUnique_ptr.allTests();
}
void Test::testShared_ptr()
{
	TestShared_ptr testShared_ptr;
	testShared_ptr.allTests();
}
void Test::testDynamicArray()
{
	TestDynamicArray testDynamicArray;
	testDynamicArray.allTests();
}