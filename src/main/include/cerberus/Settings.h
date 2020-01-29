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
string getName(const string& data, int start);
string getValue(const string& data, int start);

template<typename T> const T get (string setting);

void load(const string path);

void unloadAll();
}  // namespace Settings