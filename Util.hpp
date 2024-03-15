#ifndef UTIL_CLASS_HPP
#define UTIL_CLASS_HPP

#include <vector>

static class Util {
public:
	template<typename A, typename B>
	static void VectorToArray(const std::vector<A>& vec, B* arr) {
		std::copy(vec.begin(), vec.end(), arr);
	};
};

#endif
