#include <iostream>
#include <vector>
#include "customVector.h"

template<typename T>
void PrintVector(const kara::vector<T>& vec)
{
	std::cout << "======================\nBegin: " << vec.begin() << " - End: " << vec.end() << "\nCount: " << vec.size() << " - Capacity: " << vec.capacity() << std::endl;
	std::cout << "Data location: " << vec.data() << std::endl;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << std::endl;
	}
	std::cout << "======================\n";
}

int main()
{
	kara::vector<int> test;

	int val = 3;

	test.reserve(5);
	test.push_back(1);
	test.push_back(2);
	test.clear();
	test.push_back(val);
	test.push_back(5135);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);

	PrintVector(test);

	std::cout << std::endl;

	kara::vector<std::string> test2;

	test2.reserve(5);
	test2.emplace_back("Test");
	test2.emplace_back("Test1");
	test2.emplace_back("Test2");
	test2.emplace_back("Test3");
	test2.emplace_back("Test4");
	test2.pop_back();
	test2.emplace_back("ASDASDASD");

	test2.erase(2);
	test2.pop_back();
	test2.pop_back();
	test2.pop_back();
	test2.pop_back();

	PrintVector(test2);

	std::cout << std::endl;

	kara::vector<int> test3 = kara::vector<int>(test);

	PrintVector(test3);

	std::cout << std::endl;

	kara::vector<int> test4 = kara::vector<int>(std::move(test));

	PrintVector(test4);

	std::cout << std::endl;

	std::cout << "Test size: " << test.size() << std::endl;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	PrintVector(test);

	std::cin.get();
	return 0;
}