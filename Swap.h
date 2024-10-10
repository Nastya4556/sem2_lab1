#pragma once

#include "Move.h"

template <typename T>
inline void my_swap(T& a, T& b)
{
	T buf = move(a);
	a = move(b);
	b = move(buf);
}