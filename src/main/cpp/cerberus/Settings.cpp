#include <cerberus/Settings.h>
#include <util/Files.h>

#include <string>
#include <vector>

using namespace std;

namespace Settings {
void Load(const string path) {
    Files::ReadFile(path);
}

void UnloadAll() {
}

template <typename T> const T Get(string setting) {
    return *(T*)settings[setting];
}

template <> const int Get<int>(string setting) {
    return *(int*)settings[setting];
}

template <> const double Get<double>(string setting) {
    return *(double*)settings[setting];
}

template <> const string Get<string>(string setting) {
    return *(string*)settings[setting];
}

int Parse(const string& data, const string& parent, int start, int end) {
    for (int i = start; i < end; i++) {
        if (data[i] == '{') {
            string name = GetName(data, i - 1);
            if (parent.empty() == true) {
                i = Parse(data, name, i + 1, GetEndBracket(data, i + 1));
            } else {
                i = Parse(data, parent + sep + name, i + 1, GetEndBracket(data, i + 1));
            }
        } else if (data[i] == ':') {
            string name = GetName(data, i - 1);
            string svalue = GetValue(data, i + 1);

            if (parent.empty() == false) {
                name = parent + sep + name;
            }

            settings[name] = ParseValue(svalue);

            i += svalue.size();
        }
    }

    return end + 1;
}

void* ParseValue(const string& svalue) {
    void* value = nullptr;

    // cout << name << " = ";
    if (svalue[0] == '"') {
        value = new string(svalue.substr(1, svalue.size() - 2));
    } else if (svalue[0] == '[') {
        // cout << "array";
        int start = 1;

        value = new vector<void*>();
        for (int i = 1; i < svalue.size(); i++) {
            if (svalue[i] == ',' || svalue[i] == ']') {
                (*(vector<void*>*)value).push_back(ParseValue(svalue.substr(start, i - start)));
                start = i + 1;
            }
        }
    } else if (svalue[0] == 't') {
        value = new bool(true);
    } else if (svalue[0] == 'f') {
        value = new bool(false);
    } else if (svalue[0] >= '0' && svalue[0] <= '9') {
        bool isDecimal = false;

        for (int i = 1; i < svalue.size(); i++) {
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

bool IsDelimiter(const char& c) {
    return c == ',' || c == ':' || c == '{' || c == '}';
}

int GetEndBracket(const string& data, int start) {
    int depth = 1;

    for (int i = start; i < data.size(); i++) {
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

string GetName(const string& data, int start) {
    for (int i = start; i >= 0; i--) {
        if (IsDelimiter(data[i]) == true) {
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

string GetValue(const string& data, int start) {
    bool isString = false;
    int arrayLevel = 0;
    for (int i = start; i < data.size(); i++) {
        if (IsDelimiter(data[i]) == true && isString == false && arrayLevel == 0) {
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
}  // namespace Settings