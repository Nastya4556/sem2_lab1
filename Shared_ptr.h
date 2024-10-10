#pragma once
#include "Swap.h"

#include <cstddef>

template<typename T> class weak_ptr;

template <typename T> class shared_ptr
{
private:
	T* ptr;
	struct Control
	{
		int share_count;
		int weak_count;
		Control(int share = 0, int weak = 0)
		{
			share_count = share;
			weak_count = weak;
		}
	};
	Control* count;
	friend class weak_ptr<T>;
public:
	inline void swap(shared_ptr<T>& other)
	{
		my_swap(ptr, other.ptr);
		my_swap(count, other.count);
	}
	shared_ptr()
	{
		this->ptr = nullptr;
		this->count = nullptr;
	}
	explicit shared_ptr(T* other)
	{
		this->ptr = other;
		if (ptr != nullptr)
		{
			this->count = new Control(1, 0);
		}
		else
		{
			this->count = nullptr;
		}
	}
	shared_ptr(const shared_ptr<T>& other)
	{
		ptr = other.ptr;
		count = other.count;
		if (isFree() == false)
		{
			count->share_count += 1;
		}
	}
	shared_ptr(shared_ptr<T>&& other)
	{
		ptr = other.ptr;
		count = other.count;
		other.ptr = nullptr;
		other.count = nullptr;
	}
	~shared_ptr()
	{
		if (!count)
		{
			return;
		}
		count->share_count -= 1;
		if (!count->share_count)
		{
			delete ptr;
			if (!count->weak_count)
			{
				delete count;
			}
		}

	}
	bool isFree() const
	{
		if (ptr == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isUnique() const
	{
		if (shareCount() == 1)
		{
			return true;
		}
		else
		{
			return
				false;
		}
	}
	void reset()
	{
		shared_ptr<T> buf = shared_ptr<T>();
		this->ptr = buf.ptr;
		delete buf.ptr;
	}
	void reset(T* other)
	{
		if (ptr == other)
		{
			return;
		}
		shared_ptr<T> buf = shared_ptr<T>(other);
		this->ptr = buf.ptr;
		delete buf.ptr;
	}
	int shareCount() const
	{
		if (count == nullptr)
		{
			return 0;
		}
		else
		{
			return count->share_count;
		}
	}
	int weakCount() const
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
	T& operator *() const
	{
		return *ptr;
	}
	T* operator ->() const
	{
		return ptr;
	}
	T& operator [](int index) const
	{
		return ptr[index];
	}
	shared_ptr& operator =(const shared_ptr<T>& other)
	{
		if (ptr == other.ptr)
		{
			return *this;
		}
		shared_ptr<T> buf(other);
		swap(buf);
		return *this;
	}
	shared_ptr& operator =(shared_ptr<T>&& other)
	{
		if (ptr == other.ptr)
		{
			return *this;
		}
		swap(other);
		return *this;
	}
	shared_ptr& operator =(std::nullptr_t)
	{
		if (this->Get() == nullptr)
		{
			
		}
	}
	T* get() 
	{
		return ptr;
	}
	const T* get() const
	{
		return ptr;
	}
};

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&& ... args)
{
	return shared_ptr<T>(new T(args...));
}

template<typename T>
bool operator ==(const shared_ptr<T>& other1, const shared_ptr<T>& other2)//написать в одну строчку
{
	return (other1.get()  == other2.get());
}
template<typename T>
bool operator ==(const shared_ptr<T>& other, std::nullptr_t)
{
	return (other.get() == nullptr);
}
template<typename T>
bool operator !=(const shared_ptr<T>& other1, const shared_ptr<T>& other2)
{
	return !(other1 == other2);
}
template<typename T>
bool operator !=(const shared_ptr<T>& other, std::nullptr_t)
{
	return (!(*other == nullptr));
}
template<typename T>
bool operator <(const shared_ptr<T>& other1, const shared_ptr<T>& other2)
{
	return (other1.get() < other2.get());
}
template<typename T>
bool operator <=(const shared_ptr<T>& other1, const shared_ptr<T>& other2)
{
	return (*other1 <= *other2);
}
template<typename T>
bool operator >(const shared_ptr<T>& other1, const shared_ptr<T>& other2)
{
	return (*other1 > *other2);
}
template<typename T>
bool operator >=(const shared_ptr<T>& other1, const shared_ptr<T>& other2)
{
	return (*other1 < *other2);
}
