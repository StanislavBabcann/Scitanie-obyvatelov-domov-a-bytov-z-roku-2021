#pragma once

#include <fstream>
#include "logger.h"

namespace structures
{

    class FileLogConsumer :
        public structures::ILogConsumer
    {
    public:
        FileLogConsumer(const std::string& path);
        void logMessage(structures::LogType type, const std::string& message) override;
        void logDuration(size_t size, std::chrono::nanoseconds duration, const std::string& message) override;

    private:
        std::ofstream fileStream_;
    };
}

