#pragma once

template <typename T, typename Allocator = std::allocator<T>>
class Vector
{
	public:
		using value_type      = T;
		using allocator_type  = Allocator;
		using size_type       = typename Allocator::size_type;
		using difference_type = typename Allocator::difference_type;
		using reference       = typename Allocator::reference;
		using const_reference = typename Allocator::const_reference;
		using pointer         = typename Allocator::pointer;
		using const_pointer   = typename Allocator::const_pointer;

	public:
		Vector();
};

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector()
{
}
