#pragma once

#ifndef ERRORNTER_CLASS_HPP
#define ERRORNTER_CLASS_HPP

#include <string>
#include <map>
#include <iostream>

#define ERROR_IDK -1
#define ERROR_FILENOTEXIST -2

// this name is a stupid joke base on whom'st'd
// it's Error'nt-er =)
class Errornter {
public:
	static void coutErrorCode(int code, std::string msgDetail);
};

#endif