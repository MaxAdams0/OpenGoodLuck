#include "Errornter.hpp"

void Errornter::coutErrorCode(int code, std::string msgDetail) {
	const std::map<int, std::string> codeLookup = {
		{ ERROR_IDK, "ERROR_IDK" },
		{ ERROR_FILENOTEXIST, "ERROR_FILENOTEXIST" }
	};

	std::cout << "OpenGoodLuck::Error[" << codeLookup.at(code) << "]:	" << msgDetail << std::endl;
};