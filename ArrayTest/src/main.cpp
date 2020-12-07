#include <iostream>

#include "TestArray.h"

template<typename T, size_t S>
void PrintArray(kara::array<T, S> arr)
{
	std::cout << "================\nArray size: " << arr.size() << std::endl << std::endl;
	for (size_t i = 0; i < S; ++i)
	{
		std::cout << '\t' << arr[i] << std::endl;
	}
	std::cout << "================\n";
}


int main()
{
	kara::array<int, 5> test;
	memset(test.data(), 0, test.size() * sizeof(int));
	test[0] = 15;
	test[1] = 15;
	test[2] = 15;

#if 0
	test[5] = 15;
	static_assert(test.size() < 10, "DEBUG: Too big!");
#endif

	PrintArray(test);

	std::cout << "==================\n";

	kara::array<std::string, 9> test2;
	test2[0] = "Hello";
	test2[1] = "World";

	PrintArray(test2);

	std::cin.get();

	return 0;
}