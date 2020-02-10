#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace files {
	// TODO: Write FileExists description.
	bool fileExists (const std::string& path);

	// TODO: Write ReadFile description.
	std::string readFile(const std::string& path);

	// TODO: Write DeleteFile description.
	bool deleteFile(const std::string& path);

	// TODO: Write CreateFile description.
	bool createFile(const std::string& path);
}