#include <cerberus/ConfigManager.h>
#include <string.h>
#include <util/Files.h>

#include <string>
#include <vector>

namespace cerberus {

void ConfigManager::load(const std::string path) {
    std::string data = files::readFile(path);
    parse(data, std::string(), 0, data.size());
}

void unloadAll() {
}

int ConfigManager::parse(const std::string& data, const std::string& parent, int start, int end) {
    for (int i = start; i < end; i++) {
        if (data[i] == '{') {
            std::string name = getName(data, i - 1);
            if (parent.empty() == true) {
                i = parse(data, name, i + 1, getEndBracket(data, i + 1));
            } else {
                i = parse(data, parent + sep + name, i + 1, getEndBracket(data, i + 1));
            }
        } else if (data[i] == ':') {
            std::string name = getName(data, i - 1);
            std::string svalue = getValue(data, i + 1);

            if (parent.empty() == false) {
                name = parent + sep + name;
            }

            settings[name] = parseValue(svalue);

            i += svalue.size();
        }
    }

    return end + 1;
}

void* ConfigManager::parseValue(const std::string& svalue) {
    void* value = nullptr;

    // cout << name << " = ";
    if (svalue[0] == '"') {
        value = new std::string(svalue.substr(1, svalue.size() - 2));
    } else if (svalue[0] == '[') {
        // cout << "array";
        int start = 1;

        int objectCount = getObjectCount(svalue, start);

        value = malloc((objectCount + 1) * sizeof(void*));
        memset(value, objectCount, 1);
        int count = 1;

        for (size_t i = start; i < svalue.size(); i++) {
            if (svalue[i] == ',' || svalue[i] == ']') {
                // (*(vector<void*>*)value).push_back(parseValue(svalue.substr(start, i - start)));
                ((void**)value)[count] = (void*)parseValue(svalue.substr(start, i - start));
                start = i + 1;
                count++;
            }
        }
    } else if (svalue[0] == 't') {
        value = new bool(true);
    } else if (svalue[0] == 'f') {
        value = new bool(false);
    } else if (svalue[0] >= '0' && svalue[0] <= '9') {
        bool isDecimal = false;

        for (size_t i = 1; i < svalue.size(); i++) {
            if (svalue[i] == '.') {
                isDecimal = true;
                break;
            }
        }
        if (isDecimal == true) {
            value = new double(stod(svalue));
        } else {
            value = new int(stoi(svalue));
        }
    }

    return value;
}

bool ConfigManager::isDelimiter(const char& c) {
    return c == ',' || c == ':' || c == '{' || c == '}';
}

int ConfigManager::getEndBracket(const std::string& data, int start) {
    int depth = 1;

    for (size_t i = start; i < data.size(); i++) {
        if (data[i] == '}') {
            depth--;

            if (depth == 0) {
                return i;
            }
        } else if (data[i] == '{') {
            depth++;
        }
    }

    return start;
}

int ConfigManager::getObjectCount(const std::string& data, int start) {
    int depth = 0;
    int objectCount = 1;

    for (size_t i = start; i < data.size(); i++) {
        if (data[i] == ']') {
            depth--;

            if (depth == -1) {
                return objectCount;
            }

        } else if (data[i] == '[') {
            depth++;
        } else if (depth == 0 && data[i] == ',') {
            objectCount++;
        }
    }

    return start;
}

std::string ConfigManager::getName(const std::string& data, int start) {
    for (int i = start; i >= 0; i--) {
        if (isDelimiter(data[i]) == true) {
            if (i == start) {
                return std::string();
            } else {
                return data.substr(i + 1, start - i);
            }
        } else if (i == 0) {
            if (i == start) {
                return std::string();
            } else {
                return data.substr(i, start - i + 1);
            }
        }
    }

    return std::string();
}

std::string ConfigManager::getValue(const std::string& data, int start) {
    bool isstring = false;
    int arrayLevel = 0;
    for (size_t i = start; i < data.size(); i++) {
        if (isDelimiter(data[i]) == true && isstring == false && arrayLevel == 0) {
            if (i == start) {
                return std::string();
            } else {
                return data.substr(start, i - start);
            }
        } else if (data[i] == '"') {
            isstring = !isstring;
        } else if (data[i] == '[') {
            arrayLevel++;
        } else if (data[i] == ']') {
            arrayLevel--;
        }
    }

    return std::string();
}

}  // namespace cerberus