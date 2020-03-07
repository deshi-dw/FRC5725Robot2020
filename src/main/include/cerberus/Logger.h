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
    void print(uint32_t flag, const std::string& message, Args... args);

    template <typename... Args>
    void println(uint32_t flag, const std::string& message, Args... args);

    void println();

    std::vector<const std::pair<uint32_t, const std::string>*> getLogs(uint32_t flag);
};

}  // namespace cerberus