#include <cerberus/Settings.h>
#include <util/Files.h>

#include <string.h>
#include <string>
#include <vector>

using namespace std;

namespace cfg {
void load(const string path) {
    string data = files::readFile(path);
    parse(data, string(), 0, data.size());
}

void unloadAll() {
}

template <typename T>
const bool get(string setting, T& value) {
    if (settings[setting] != nullptr) {
        value = *(T*)settings[setting];
        return true;
    }

    return false;
}

template <>
const bool get<bool>(string setting, bool& value) {
    if (settings[setting] != nullptr) {
        value = *(bool*)settings[setting];
        return true;
    }

    return false;
}

template <>
const bool get<int>(string setting, int& value) {
    if (settings[setting] != nullptr) {
        value = *(int*)settings[setting];
        return true;
    }

    return false;
}

template <>
const bool get<double>(string setting, double& value) {
    if (settings[setting] != nullptr) {
        value = *(double*)settings[setting];
        return true;
    }

    return false;
}

template <>
const bool get<string>(string setting, string& value) {
    if (settings[setting] != nullptr) {
        value = *(string*)settings[setting];
        return true;
    }

    return false;
}

template <typename T>
const int getArray(string setting, T* value) {
	value = *(T*)settings[setting]+1;
    return *(int*)settings[setting]+0;
}

int parse(const string& data, const string& parent, int start, int end) {
    for (int i = start; i < end; i++) {
        if (data[i] == '{') {
            string name = getName(data, i - 1);
            if (parent.empty() == true) {
                i = parse(data, name, i + 1, getEndBracket(data, i + 1));
            } else {
                i = parse(data, parent + sep + name, i + 1, getEndBracket(data, i + 1));
            }
        } else if (data[i] == ':') {
            string name = getName(data, i - 1);
            string svalue = getValue(data, i + 1);

            if (parent.empty() == false) {
                name = parent + sep + name;
            }

            settings[name] = parseValue(svalue);

            i += svalue.size();
        }
    }

    return end + 1;
}

void* parseValue(const string& svalue) {
    void* value = nullptr;

    // cout << name << " = ";
    if (svalue[0] == '"') {
        value = new string(svalue.substr(1, svalue.size() - 2));
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
				((void**)value)[count] = (void*) parseValue(svalue.substr(start, i - start));
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

bool isDelimiter(const char& c) {
    return c == ',' || c == ':' || c == '{' || c == '}';
}

int getEndBracket(const string& data, int start) {
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

int getObjectCount(const string& data, int start) {
    int depth = 0;
    int objectCount = 1;

    for (size_t i = start; i < data.size(); i++) {
        if (data[i] == ']') {
            depth--;

			if(depth == -1) {
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

string getName(const string& data, int start) {
    for (int i = start; i >= 0; i--) {
        if (isDelimiter(data[i]) == true) {
            if (i == start) {
                return string();
            } else {
                return data.substr(i + 1, start - i);
            }
        } else if (i == 0) {
            if (i == start) {
                return string();
            } else {
                return data.substr(i, start - i + 1);
            }
        }
    }

    return string();
}

string getValue(const string& data, int start) {
    bool isString = false;
    int arrayLevel = 0;
    for (size_t i = start; i < data.size(); i++) {
        if (isDelimiter(data[i]) == true && isString == false && arrayLevel == 0) {
            if (i == start) {
                return string();
            } else {
                return data.substr(start, i - start);
            }
        } else if (data[i] == '"') {
            isString = !isString;
        } else if (data[i] == '[') {
            arrayLevel++;
        } else if (data[i] == ']') {
            arrayLevel--;
        }
    }

    return string();
}
}  // namespace cfg