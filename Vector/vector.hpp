#pragma once

#include <memory>
#include <exception>

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

		reference operator [](const size_type index) noexcept;
		const_reference operator [](const size_type index) const noexcept;

		void push_back(reference value);

	private:
		void _reallocate();
		std::unique_ptr<T[]> _allocate(size_type n);
		void _check_and_realloc();

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

	typename Iterator::reference
	operator *()
	{
		return *m_p;
	}

	Iterator operator ++(int)
	{
		Iterator ret = m_p;
		++m_p;
		return ret;
	}

	Iterator& operator ++()
	{
		++m_p;
		return *this;
	}

	bool operator ==(const Iterator& other)
	{
		return m_p == other.m_p;
	}

	bool operator !=(const Iterator& other)
	{
		return m_p != other.m_p;
	}

	Iterator operator +(const typename Iterator::difference_type n)
	{
		return Iterator(m_p + n);
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

template <typename T, typename Allocator>
void Vector<T, Allocator>::_reallocate()
{
	if (capacity() == 0)
	{
		m_data     = _allocate(4);
		m_begin    = m_end = m_data.get();
		m_capacity = m_begin + 4;

		return;
	}

	const size_type old_capacity = capacity();
	const size_type new_capacity = old_capacity * 2;
	auto new_memory = _allocate(new_capacity);

	if (new_memory == nullptr)
		throw std::bad_alloc();

	auto raw_pointer_new = new_memory.get();
	auto raw_pointer_old = m_data.get();
	for (auto i = 0; i < old_capacity; ++i)
		raw_pointer_new[i] = std::move(raw_pointer_old[i]);

	m_begin    = raw_pointer_new;
	m_end      = raw_pointer_new + old_capacity;
	m_capacity = raw_pointer_new + new_capacity;

	m_data = std::move(new_memory);
}

template <typename T, typename Allocator>
std::unique_ptr<T[]> Vector<T, Allocator>::_allocate(size_type n)
{
	Allocator allocator;
	return std::unique_ptr<T[]>(allocator.allocate(n));
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::operator [](const size_type index) noexcept
{
	return m_data.get()[index];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::operator [](const size_type index) const noexcept
{
	return m_data.get()[index];
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::_check_and_realloc()
{
	if (m_end == m_capacity)
		_reallocate();
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(reference value)
{
	_check_and_realloc();
	*m_end++ = value;
}
