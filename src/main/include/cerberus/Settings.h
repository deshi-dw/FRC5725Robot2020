#pragma once

#include <map>
#include <string>

using namespace std;

namespace Settings {
namespace {
map<const string, void*> settings;
const string sep = "::";

int Parse(const string& data, const string& parent, int start, int end);
void* ParseValue(const string& svalue);
bool IsDelimiter(const char& c);
int GetEndBracket(const string& data, int start);
string GetName(const string& data, int start);
string GetValue(const string& data, int start);
}  // namespace

template<typename T> const T Get (string setting);

void Load(const string path);

void UnloadAll();
}  // namespace Settings