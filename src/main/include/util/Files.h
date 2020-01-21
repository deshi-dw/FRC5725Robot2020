#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace util {
	// TODO: Write FileExists description.
	bool FileExists (const string& path);

	// TODO: Write ReadFile description.
	string& ReadFile(const string& path);

	// TODO: Write DeleteFile description.
	bool DeleteFile(const string& path);

	// TODO: Write CreateFile description.
	bool CreateFile(const string& path);
}