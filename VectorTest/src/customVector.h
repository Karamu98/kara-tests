#pragma once

#include <assert.h>

namespace kara
{
	template<typename T>
	class vector
	{
	public:
		vector<T>();
		vector<T>(const vector<T>& other);
		vector<T>(vector<T>&& other);
		~vector<T>();

		void reserve(size_t newSize);
		void push_back(T&& value);
		void push_back(const T& value);

		template<typename... Args>
		void emplace(int index, Args&&... args);
		template<typename... Args>
		void emplace_back(Args&&... args);

		void pop_back();
		void erase(size_t index);

		void clear();
		T& begin() const;
		T& end() const;
		const size_t capacity() const;
		const size_t size() const;

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		const T* data() const;

	private:
		T* m_data;
		size_t m_size;
		size_t m_capacity;
	};

	template<typename T>
	inline vector<T>::vector() : m_data(nullptr), m_capacity(0), m_size(0)
	{
	}

	template<typename T>
	inline vector<T>::vector(const vector<T>& other)
	{
		m_data = (T*)::operator new(other.m_capacity * sizeof(T));
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		// Calls copy constructor, don't use memcpy
		for (size_t i = 0; i < m_size; ++i)
		{
			new(&m_data[i]) T(other.m_data[i]);
		}
	}

	template<typename T>
	inline vector<T>::vector(vector<T>&& other)
	{
		if (this == &other)
		{
			return;
		}

		clear();
		::operator delete(m_data, m_capacity * sizeof(T));

		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	template<typename T>
	inline vector<T>::~vector()
	{
		clear(); // Call destructor on all
		::operator delete(m_data, m_capacity * sizeof(T)); // Unalloc without destructors
	}

	template<typename T>
	inline void vector<T>::reserve(size_t newCapacity)
	{
		if (newCapacity <= m_capacity)
		{
			return;
		}

		T* newData = (T*)::operator new(newCapacity * sizeof(T));

		if (newCapacity < m_size)
		{
			m_size = newCapacity;
		}

		for (size_t i = 0; i < m_size; ++i)
		{
			new(&newData[i]) T(std::move(m_data[i]));
			m_data[i].~T();
		}

		::operator delete(m_data, m_capacity * sizeof(T));
		m_data = newData;
		m_capacity = newCapacity;
	}

	template<typename T>
	inline void vector<T>::push_back(T&& value)
	{
		if (m_size >= m_capacity)
		{
			reserve(m_capacity + 1);
		}

		new(&m_data[m_size]) T(std::move(value));
		m_size++;
	}

	template<typename T>
	inline void vector<T>::push_back(const T& value)
	{
		if (m_size >= m_capacity)
		{
			reserve(m_capacity + 1);
		}

		new(&m_data[m_size]) T(value);
		m_size++;
	}

	template<typename T>
	template<typename... Args>
	inline void vector<T>::emplace(int index, Args&&... args)
	{
		if (index >= m_capacity)
		{
			return;
		}

		if (index >= m_size)
		{
			m_size++;
		}

		new(&m_data[m_size]) T(std::forward<Args>(args)...); // Construct object with arguments at data location
	}

	template<typename T>
	template<typename... Args>
	inline void vector<T>::emplace_back(Args&&... args)
	{
		if (m_size >= m_capacity)
		{
			reserve(m_capacity + 1);
		}

		new(&m_data[m_size]) T(std::forward<Args>(args)...); // Construct object with arguments at data location
		m_size++;
	}

	template<typename T>
	inline void vector<T>::pop_back()
	{
		assert(m_size > 0);

		m_size--;
		m_data[m_size].~T();
	}

	template<typename T>
	inline void vector<T>::erase(size_t index)
	{
		assert(index < m_size);

		m_data[index].~T();
	}

	template<typename T>
	inline void vector<T>::clear()
	{
		// Calling the destructor on all elements
		for (size_t i = 0; i < m_size; ++i)
		{
			m_data[i].~T();
		}

		m_size = 0;
	}

	template<typename T>
	inline T& vector<T>::begin() const
	{
		return m_data[0];
	}

	template<typename T>
	inline T& vector<T>::end() const
	{
		return m_data[m_size-1];
	}

	template<typename T>
	inline const size_t vector<T>::size() const
	{
		return m_size;
	}

	template<typename T>
	inline T& vector<T>::operator[](size_t index)
	{
		assert(index < m_size);

		return m_data[index];
	}

	template<typename T>
	inline const T& vector<T>::operator[](size_t index) const
	{
		assert(index < m_size);

		return m_data[index];
	}

	template<typename T>
	inline const size_t vector<T>::capacity() const
	{
		return m_capacity;
	}

	template<typename T>
	inline const T* vector<T>::data() const
	{
		return m_data;
	}
}