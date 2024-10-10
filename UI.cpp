#include <iostream>

#include "UI.h"
#include "TestDynamicArray.h"
#include "TestShared_ptr.h"
#include "TestUnique_ptr.h"

void startUI()
{
	std::cout << "Choose which test you want to do:\n";
	std::cout << "0 - finish program\n";
	std::cout << "1 - test with dynamic array\n";
	std::cout << "2 - test with shared_ptr\n";
	std::cout << "3 - test with unique_ptr\n";
	int selectedTest{};
	std::cin >> selectedTest;
	while (selectedTest != 0)
	{
		while (selectedTest < 0 || selectedTest > 3)
		{
			std::cout << "The wrong number was entered.Try again\n";
			std::cin >> selectedTest;
		}
		if (selectedTest == 1)
		{
			TestDynamicArray testDynamicArray;
			testDynamicArray.allTests();
			std::cout << "The tests were successfull\n";
		}
		if (selectedTest == 2)
		{
			TestShared_ptr testShared_ptr;
			testShared_ptr.allTests();
			std::cout << "The tests were successfull\n";
		}
		if (selectedTest == 3)
		{
			TestUnique_ptr testUnique_ptr;
			testUnique_ptr.allTests();
			std::cout << "The tests were successfull\n";
		}
		std::cout << "\n\nChoose which test you want to do:\n";
		std::cout << "0 - finish program\n";
		std::cout << "1 - test with dynamic array\n";
		std::cout << "2 - test with shared_ptr\n";
		std::cout << "3 - test with unique_ptr\n";
		std::cin >> selectedTest;
	}
	
	std::cout << "You have finished program\n";
}