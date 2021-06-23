#include <iostream>

#include "vector.hpp"

int main()
{
	Vector<int> vec;

	for (int i = 0; i < 5; ++i)
		vec.push_back(i);

	for (auto it = std::begin(vec); it != std::end(vec); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Vector size: " << vec.size() << std::endl;
	std::cout << "Vector capacity: " << vec.capacity() << std::endl;

	return 0;
}
