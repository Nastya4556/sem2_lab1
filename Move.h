#pragma once

template <typename T>
inline T&& move(T& in)
{
	return static_cast<T&&>(in);
}

template<typename T>
inline T&& move(T&& in)
{
	return static_cast<T&&>(in);
}