#pragma once

#include <map>
#include <string>

using namespace std;

namespace cfg {
namespace {
map<const string, void*> settings;
const string sep = "::";
}  // namespace

int parse(const string& data, const string& parent, int start, int end);
void* parseValue(const string& svalue);
bool isDelimiter(const char& c);
int getEndBracket(const string& data, int start);
int getObjectCount(const string& data, int start);
string getName(const string& data, int start);
string getValue(const string& data, int start);

template<typename T> const bool get (string setting, T& value);
template<> const bool get<int> (string setting, int& value);
template<> const bool get<double> (string setting, double& value);
template<> const bool get<bool> (string setting, bool& value);
template<> const bool get<string> (string setting, string& value);

template <typename T> const int getArray(string setting, T* value);

void load(const string path);

void unloadAll();
}  // namespace Settings