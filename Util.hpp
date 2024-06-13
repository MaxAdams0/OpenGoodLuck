#pragma once

#ifndef UTIL_CLASS_HPP
#define UTIL_CLASS_HPP

#include <vector>

static class Util {
public:
	template<typename T>
	static T* vecToCArray(const std::vector<T>& vector) {
		int size = vector.size();
		T* new_array = new T[size];

		for (int i = 0; i < size; i++) {
			new_array[i] = vector.at(i);
		}

		return new_array;
	}
};

#endif