#pragma once

#include <mutex>

template <typename T>
class Synchronized {
public:
	explicit Synchronized(T initial = T())
		: value(move(initial))
	{
	}

	struct Access {
		T& ref_to_value;
		lock_guard<mutex> guard;
	};

	Access GetAccess()
	{
		return { value, lock_guard(m) };
	}

	struct AccessConst {
		const T& ref_to_value;
		lock_guard<mutex> guard;
	};

	AccessConst GetAccess() const
	{
		return { value, lock_guard(m) };
	}
private:
	T value;
	mutable mutex m;
};