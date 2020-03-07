#pragma once

#include <map>
#include <string>

namespace cerberus {

class ConfigManager {
   private:
    std::map<const std::string, void*> settings;
    const std::string sep = "::";

   public:
    int parse(const std::string& data, const std::string& parent, int start, int end);

    void* parseValue(const std::string& svalue);

    bool isDelimiter(const char& c);

    int getEndBracket(const std::string& data, int start);

    int getObjectCount(const std::string& data, int start);

    std::string getName(const std::string& data, int start);

    std::string getValue(const std::string& data, int start);

    template <typename T>
    const bool get(std::string setting, T& value) {
        if (settings[setting] != nullptr) {
            value = *(T*)settings[setting];
            return true;
        }

        return false;
    }

    template <typename T>
    const int getArray(std::string setting, T* value) {
        value = *(T*)settings[setting] + 1;
        return *(int*)settings[setting] + 0;
    }

    void load(const std::string path);

    void unloadAll();
};

}  // namespace cerberus