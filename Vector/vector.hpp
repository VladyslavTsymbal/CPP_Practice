#pragma once

#include <iostream>

template <typename T, typename Allocator = std::allocator<T>>
class Vector
{
	public:
		Vector();
};

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector()
{
	std::cout << "Hello from Vector!\n";
}
