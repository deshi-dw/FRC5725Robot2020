#pragma once

#include <map>
#include <string>

namespace cfg {
namespace {
std::map<const std::string, void*> settings;
const std::string sep = "::";
}  // namespace

int parse(const std::string& data, const std::string& parent, int start, int end);
void* parseValue(const std::string& svalue);
bool isDelimiter(const char& c);
int getEndBracket(const std::string& data, int start);
int getObjectCount(const std::string& data, int start);
std::string getName(const std::string& data, int start);
std::string getValue(const std::string& data, int start);

template<typename T> const bool get (std::string setting, T& value);
template<> const bool get<int> (std::string setting, int& value);
template<> const bool get<double> (std::string setting, double& value);
template<> const bool get<bool> (std::string setting, bool& value);
template<> const bool get<std::string> (std::string setting, std::string& value);

template <typename T> const int getArray(std::string setting, T* value);

void load(const std::string path);

void unloadAll();
}  // namespace Settings