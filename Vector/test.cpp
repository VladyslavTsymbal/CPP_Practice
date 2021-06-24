#include <iostream>

#include "vector.hpp"

template <typename T>
void print(const Vector<T>& vec)
{
	for (auto it = std::begin(vec); it != std::end(vec); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	Vector<int> vec;

	for (int i = 0; i < 5; ++i)
		vec.push_back(i);

	print(vec);

	std::cout << "Vector size: " << vec.size() << std::endl;
	std::cout << "Vector capacity: " << vec.capacity() << std::endl;

	return 0;
}
