#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace files {
	// TODO: Write FileExists description.
	bool fileExists (const string& path);

	// TODO: Write ReadFile description.
	string readFile(const string& path);

	// TODO: Write DeleteFile description.
	bool deleteFile(const string& path);

	// TODO: Write CreateFile description.
	bool createFile(const string& path);
}