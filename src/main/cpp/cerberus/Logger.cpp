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