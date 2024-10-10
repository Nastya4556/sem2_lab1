#pragma once

#include "Shared_ptr.h"
#include "Swap.h"

template<typename T> class weak_ptr
{
private:
	T* ptr;
	typename shared_ptr<T>::Control* count;
public:
	inline void swap(weak_ptr<T>& other)
	{
		my_swap(ptr, other.ptr);
		my_swap(count, other.count);
	}
	weak_ptr()
	{
		this->ptr = nullptr;
		this->count = nullptr;
	}
	weak_ptr(const shared_ptr<T>& other)
	{
		this->ptr = other.ptr;
		this->count = other.count;
		if (count != nullptr)
		{
			count->weak_count += 1;
		}
	}
	weak_ptr(const weak_ptr<T>& other)
	{
		this->ptr = other.ptr;
		this->count = other.count;
		if (count != nullptr)
		{
			count->weak_count += 1;
		}
	}
	~weak_ptr()
	{
		if (!count)
		{
			return;
		}
		count->weak_count -= 1;
		if (!count->weak_count && !count->share_count)
		{
			delete count;
		}
	}
	bool isExpired()
	{
		if (count == nullptr)
		{
			return true;
		}
		else
		{
			if (count->share_count == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	int weakCount()
	{
		if (count == nullptr)
		{
			return 0;
		}
		else
		{
			return count->weak_count;
		}
	}
	shared_ptr<T> lock()
	{
		return shared_ptr<T>(*this);
	}
	weak_ptr& operator =(const weak_ptr<T>& other)
	{
		if (ptr == other.ptr)
		{
			return *this;
		}
		weak_ptr<T> buf(other);
		swap(buf);
		return *this;
	}
	weak_ptr& operator =(weak_ptr<T>&& other)
	{
		if (ptr == other.ptr)
		{
			return *this;
		}
		swap(other);
		return *this;
	}
};