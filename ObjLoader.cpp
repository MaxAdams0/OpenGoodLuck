#include "ObjLoader.hpp"

ObjLoader::Mesh ObjLoader::NewMesh(const char* filename) {
	Mesh newMesh;
	// =============== Read file and check read success ===============
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Unable to open file: '" << filename << "'\n";
		return Mesh();
	}

	std::string line;
	// =============== Parse the file line-by-line ===============
	while (std::getline(file, line)) {
		std::string indicator = GetValueIndicator(line);

		if (indicator == "v") { // vertex positions
			std::string content = GetContent(line, indicator);
			std::vector<std::string> positions = SplitStrByDelimiter(content, " ");
			std::vector<float> floats = StringsToFloats(positions);
			Position newPos;
			newPos.x = floats.at(0);
			newPos.y = floats.at(1);
			newPos.z = floats.at(2);
			newMesh.texCoords.emplace_back(newPos);
		}
		if (indicator == "vt") { // texture coordinates
			std::string content = GetContent(line, indicator);
			std::vector<std::string> coords = SplitStrByDelimiter(content, " ");
			std::vector<float> floats = StringsToFloats(coords);
			TexCoord newTexC;
			newTexC.u = floats.at(0);
			newTexC.v = floats.at(1);
			newMesh.texCoords.emplace_back(newTexC);
		}
		else if (indicator == "f") { // face indices
			std::string content = GetContent(line, indicator);
			std::vector<std::string> indiceGroups = SplitStrByDelimiter(content, " ");
			for (auto group : indiceGroups) {
				std::vector<std::string> indices = SplitStrByDelimiter(group, "/");
				std::vector<int> ints = StringsToInts(indices);
				// the first one is the pos indices, we need that one only
				newMesh.indices.emplace_back(ints.at(0));
			}
		}
	}

	return newMesh;
}

std::string ObjLoader::GetValueIndicator(std::string line) {
	return line.substr(0, line.find_first_of(' '));
}

std::string ObjLoader::GetContent(std::string line, const std::string indicator) {
	return line.substr(indicator.length() + 1, line.length()); // +1 is bc of space
}

std::vector<std::string> ObjLoader::SplitStrByDelimiter(std::string str, const std::string delim) {
	std::vector<std::string> elemVec;

	// Works perfectly but even Jesus got impatient at me writing this
	while (!str.empty()) {
		size_t delim_i = isValidPos(str.find_last_of(delim)); // Get valid index of delimiter
		// If not the first element, remove the delimiter too
		std::string elem = str.substr(delim_i == 0 ? 0 : delim_i + 1);
		str = str.substr(0, delim_i); // Remove element from str
		elemVec.insert(elemVec.begin(), elem); // Add element to vector in reverse order
	}

	return elemVec;
}

std::vector<float> ObjLoader::StringsToFloats(const std::vector<std::string> strs) {
	std::vector<float> floats;

	for (auto str : strs) {
		floats.emplace_back(std::stof(str));
	}

	return floats;
}

std::vector<int> ObjLoader::StringsToInts(const std::vector<std::string> strs) {
	std::vector<int> ints;

	for (auto str : strs) {
		ints.emplace_back(std::stoi(str));
	}

	return ints;
}

int ObjLoader::isValidPos(const size_t pos) {
	return (pos == std::string::npos) ? 0 : pos;
}