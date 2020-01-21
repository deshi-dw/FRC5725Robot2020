#include <util/Files.h>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool CreateFile(const string& path) {
	// Open a file with the specified path under write mode.
	// This will create a file if non are present under that name.
	FILE* file = fopen (path.c_str(), "w");

	if(file != 0) {
		// TODO: Log file create.
		// If the file could be created, return true.
		return true;
	}
	else {
		// TODO: Log error when creating file.
		// If the file couldn't be created, return false.
		return false;
	}
}

bool DeleteFile(const string& path) {
	if(remove(path.c_str()) == 0) {
		// If the file is removed, return true.
		// TODO: Log deletion of file.
		return true;
	}
	else {
		// If the file is not removed, return false.
		// TODO: Log failiure to delete file.
		return false;
	}
}

string& ReadFile(const string& path) {
	// Open the file specifed under read mode.
	FILE* file = fopen (path.c_str (), "r");
	string sbuffer;

	// Get the size of the file by seeking the end of file and storing it in size.
	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	// Put the stream position back to the start.
	rewind (file);

	// Allocate a char buffer to store the file contents.
	char* buffer = (char*)malloc(sizeof(char) * size);
	if(buffer == nullptr) {
		// TODO: Log memory assignment error.
		return sbuffer;
	}

	if(fread(buffer, 1, size, file) != 0) {
		// If the file was successfully read, create a string object from the char buffer.
		sbuffer = string(buffer);
		
		// Clean up the char buffer from memory and close the file.
		free(buffer);
		fclose(file);

		// Return the string buffer.
		return sbuffer;
	}
	else {
		// The file was read unsuccessfully.
		return sbuffer;
	}
}

bool FileExists (const string& path) {
	// Open the file specifed under read mode.
	FILE* file = fopen (path.c_str (), "r");

	if (file != 0) {
		// If the file exists, close it and return true.
		fclose (file);
		return true;
	}
	else {
		// If the file couldn't be opened, return false.
		return false;
	}
}