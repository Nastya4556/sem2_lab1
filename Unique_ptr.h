#pragma once
#include <cstddef>

#include "Swap.h"
#include "TypeTraits.h"
#include "Deleter.h"
#include "Move.h"
template<typename T, class Deleter = My_Deleter<T>>
class unique_ptr
{
	using U = remove_extent_t<T>;
private:
	U* ptr;
	Deleter my_delete = Deleter();
public:
	inline void swap(unique_ptr<T, Deleter>& other)
	{
		my_swap(ptr, other.ptr);
	}
	unique_ptr() :ptr(nullptr) {};
	explicit unique_ptr(std::nullptr_t) :unique_ptr() {};
	explicit unique_ptr(U* other) :ptr(move(other)) {};
	unique_ptr(const unique_ptr<T, Deleter>& other) = delete;
	unique_ptr(unique_ptr<T, Deleter>&& other) :ptr(other.ptr)
	{
		other.ptr = nullptr;
	}
	virtual ~unique_ptr()
	{
		my_delete(ptr);
	}
	bool isFree() const
	{
		return ptr == nullptr;
	}
	void reset()
	{
		unique_ptr<T, Deleter> buf = unique_ptr<T, Deleter>();
		swap(buf);
	}
	U* release()
	{
		U* buf = ptr;
		ptr = nullptr;
		return buf;
	}
	U* get() const
	{
		return ptr;
	}
	U& operator*() const
	{
		return *ptr;
	}
	U* operator->() const
	{
		return ptr;
	}
	template<typename K = T, typename = enable_if_t<typename is_array<K>::value>>
	U& operator[](int index) const
	{
		return ptr[index];
	}
	unique_ptr& operator =(const unique_ptr<T, Deleter>& other) = delete;
	unique_ptr& operator = (std::nullptr_t)
	{
		unique_ptr<T, Deleter> buf;
		swap(buf);
		return *this;
	}
	unique_ptr& operator =(unique_ptr<T, Deleter>&& other)
	{
		unique_ptr < T, Deleter> buf(move(other));
		swap(buf);
		return *this;
	}
};

template<typename T, class Deleter = My_Deleter<T>, typename... Args>
unique_ptr<T, Deleter> make_unique(Args&& ... args)
{
	return unique_ptr<T, Deleter>(new T(args...));
}

template<typename T, class Deleter = My_Deleter<T>, typename... Args>
unique_ptr<T[], Deleter> make_unique(size_t size, Args&& ... args)
{
	T* ptr = new T[size];
	for (int i = 0; i < size; i++)
	{
		ptr[i] = T(args...);
	}
	return unique_ptr<T, Deleter>(ptr);
}

template<typename T, class Deleter = My_Deleter<T>>
unique_ptr<T[], Deleter> make_unique(size_t size)
{
	T* ptr = new T[size];
	return unique_ptr<T, Deleter>(ptr);
}

template<typename T, class Deleter = My_Deleter<T>>
bool operator ==(const unique_ptr<T, Deleter>& other1, const unique_ptr<T, Deleter>& other2)
{
	return other1.get() == other2.get();
}
template<typename T, class Deleter = My_Deleter<T>>
bool operator !=(const unique_ptr<T, Deleter>& other1, const unique_ptr<T, Deleter>& other2)
{
	return !(other1 == other2);
}

template<typename T, class Deleter = My_Deleter<T>>
bool operator == (const unique_ptr<T, Deleter>& other, std::nullptr_t)
{
	return other.get() == nullptr;
}

template<typename T, class Deleter = My_Deleter<T>>
bool operator ==(std::nullptr_t, const unique_ptr<T, Deleter>& other)
{
	return other.get() == nullptr;
}

template<typename T, class Deleter = My_Deleter<T>>
bool operator !=(const unique_ptr<T, Deleter>& other, std::nullptr_t)
{
	return !(other == nullptr);
}

template<typename T, class Deleter = My_Deleter<T>>
bool operator !=(std::nullptr_t, const unique_ptr<T, Deleter>& other)
{
	return !(other == nullptr);
}