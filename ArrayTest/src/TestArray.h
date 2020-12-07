#pragma once

#include <assert.h>

namespace kara
{
	template<typename T, size_t S>
	class array
	{
	public:
		constexpr size_t size() const;

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		T* data();
		const T* data() const;

	private:
		T m_data[S];
	};

	template<typename T, size_t S>
	inline constexpr size_t array<T, S>::size() const
	{
		return S;
	}

	template<typename T, size_t S>
	inline T& array<T, S>::operator[](size_t index)
	{
		assert(index < S);

		return m_data[index];
	}

	template<typename T, size_t S>
	inline const T& array<T, S>::operator[](size_t index) const
	{
		assert(index < S);

		return m_data[index];
	}

	template<typename T, size_t S>
	inline T* array<T, S>::data()
	{
		return m_data;
	}

	template<typename T, size_t S>
	inline const T* array<T, S>::data() const
	{
		return m_data;
	}

}
