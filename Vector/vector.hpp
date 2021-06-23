#pragma once

#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class Vector
{
	public:
		template <typename A>
		struct Iterator;

		using value_type      = T;
		using allocator_type  = Allocator;
		using size_type       = typename Allocator::size_type;
		using difference_type = typename Allocator::difference_type;
		using reference       = typename Allocator::reference;
		using const_reference = typename Allocator::const_reference;
		using pointer         = typename Allocator::pointer;
		using const_pointer   = typename Allocator::const_pointer;
		using iterator        = Iterator<value_type>;
		using const_iterator  = Iterator<const value_type>;

	public:
		Vector() = default;

		iterator       begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;

		iterator       end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;

		size_type size() const noexcept;
		size_type capacity() const noexcept;

	private:
		std::unique_ptr<T[]> m_data = nullptr;
		iterator m_begin            = nullptr;
		iterator m_end              = nullptr;
		iterator m_capacity         = nullptr;
};

template <typename T, typename Allocator>
template <typename A>
struct Vector<T, Allocator>::Iterator :
	public std::iterator<std::random_access_iterator_tag, A>
{
	Iterator(pointer p) : m_p(p)
	{
	}

	bool operator < (const Iterator other)
	{
		return m_p < other.m_p;
	}

	typename Iterator::difference_type
	operator -(const Iterator other) const
	{
		return m_p - other.m_p;
	}

	private:
		pointer m_p;
};

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::begin() noexcept
{
	return m_begin;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::begin() const noexcept
{
	return m_begin;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cbegin() const noexcept
{
	return begin();
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::end() noexcept
{
	return m_end;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::end() const noexcept
{
	return m_end;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cend() const noexcept
{
	return end();
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::size() const noexcept
{
	return m_end - m_begin;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::capacity() const noexcept
{
	return m_capacity - m_begin;
}
