#include <cerberus/Logger.h>

#include <map>
#include <string>
#include <vector>

namespace cerberus {

Logger::Logger() {
    m_logs.reserve(256);

    m_flags["INFO"] = info;
    m_flags["WARNING"] = warning;
    m_flags["ERROR"] = error;
}

Logger::~Logger() {
    m_flags.clear();
}

uint32_t Logger::addFlag(const std::string& flag_name) {
    if (flagCount >= 32) {
        print(warning, "the maximum number of 32 flags reached. No more can be created.");
        return 0;
    }

    m_flags[flag_name] = flagCount >> 1;
    flagCount++;

    return m_flags[flag_name];
}

uint32_t Logger::getFlag(const std::string& flag_name) {
    return m_flags[flag_name];
}

void Logger::removeFlag(const std::string& flag_name) {
    m_flags.erase(flag_name);
}

void Logger::clear() {
    m_logs.clear();
}

template <typename... Args>
void Logger::print(uint32_t flag, const std::string& message, Args... args) {
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
void Logger::println(uint32_t flag, const std::string& message, Args... args) {
    print(flag, message + "\r\n", args...);
}

void Logger::println() {
    print(0, "\r\n");
}

std::vector<const std::pair<uint32_t, const std::string>*> Logger::getLogs(uint32_t flag) {
    std::vector<const std::pair<uint32_t, const std::string>*> return_logs;

    for (size_t i = 0; i < m_logs.size(); i++) {
        if ((m_logs[i].first & flag) != 0) {
            return_logs.push_back(&m_logs[i]);
        }
    }

    return return_logs;
}

}  // namespace cerberus