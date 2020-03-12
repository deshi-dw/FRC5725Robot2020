#pragma once

#include <CompilerSettings.h>

#include <map>
#include <string>
#include <vector>

#if LOGGER_PRINT_TO_COUT
#include <iostream>
#endif

namespace cerberus {

class Logger {
   private:
    std::map<const std::string, uint32_t> m_flags;
    std::vector<std::pair<uint32_t, const std::string>> m_logs;
    int flagCount;

   public:
    const static uint32_t info = 0b100;
    const static uint32_t warning = 0b010;
    const static uint32_t error = 0b001;

    Logger();

    ~Logger();

    uint32_t addFlag(const std::string& flag_name);

    uint32_t getFlag(const std::string& flag_name);

    void removeFlag(const std::string& flag_name);

    void clear();

    template <typename... Args>
    void print(uint32_t flag, const std::string& message, Args... args) {
        size_t size = std::snprintf(nullptr, 0, message.c_str(), args...) + 1;
        if (size <= 0) {
#if LOGGER_PRINT_TO_COUT
            std::cout << "error when formatting print message.";
#endif
            return;
        }

        char* buffer = new char[size];
        std::snprintf(buffer, size, message.c_str(), args...);
        m_logs.push_back(std::make_pair(flag, std::string(buffer, buffer + size - 1)));

        delete buffer;

#if LOGGER_PRINT_TO_COUT
        if (flag == 0) {
            std::cout << m_logs[m_logs.size() - 1].second;
        } else {
            std::string flag_string = "";
            for (const std::pair<const std::string, uint32_t>& value : m_flags) {
                if ((value.second & flag) != 0) {
                    if (flag_string.empty()) {
                        flag_string += value.first;
                    } else {
                        flag_string += "|" + value.first;
                    }
                }
            }

            std::cout << "[" << flag_string << "] " << m_logs[m_logs.size() - 1].second;
        }
#endif
    }

    template <typename... Args>
    void println(uint32_t flag, const std::string& message, Args... args) {
        print(flag, message + "\r\n", args...);
    }

    void println();

    std::vector<const std::pair<uint32_t, const std::string>*> getLogs(uint32_t flag);
};

}  // namespace cerberus