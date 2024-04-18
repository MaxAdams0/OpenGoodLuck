#pragma once

#ifndef OBJLOADER_CLASS_HPP
#define OBJLOADER_CLASS_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>

class ObjLoader {
public:
	struct Position {
		GLfloat x, y, z;
	};

	struct Color {
		GLfloat r, g, b;
	};

	struct TexCoord {
		GLfloat u, v; // same as (s, t) or (x, y)
	};

	struct Mesh {
		std::vector<Position> positions;
		std::vector<TexCoord> texCoords;
		std::vector<GLuint> indices;
	};


	static Mesh NewMesh(const char* filename);

private:
	static std::string GetValueIndicator(std::string line);
	static std::string GetContent(std::string line, const std::string indicator);
	static std::vector<std::string> SplitStrByDelimiter(std::string line, const std::string delim);
	static std::vector<float> StringsToFloats(const std::vector<std::string> strs);
	static std::vector<int> StringsToInts(const std::vector<std::string> strs);
	static int isValidPos(const size_t pos);
};

#endif