#pragma warning(disable:4996)

#include <iomanip>
#include <iostream>
#include <chrono>

#include "Logging.hpp"

const char* STDOUT_FILENAME = "<stdout>";

Logging& Logging::Get() {
    static Logging logging;
    return logging;
}

void Logging::writeLineRaw(const std::string& line) {
    if (filename_.empty()) {
        return;
    }
    else {
        auto& file = (filename_ == STDOUT_FILENAME) ? std::cout : file_;
        file << line << std::endl;
    }
}

void Logging::setFilename(const std::string& filename) {
    filename_ = filename;
    if (filename.empty() || filename == STDOUT_FILENAME) {
        file_.close();
    }
    if (filename.empty()) return;
    if (filename != STDOUT_FILENAME) file_.open(filename, std::ios_base::app);
    auto& file = (filename == STDOUT_FILENAME) ? std::cout : file_;
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    file << "\n=== Log started --- " << std::put_time(std::localtime(&time), "%Y.%m.%d %T") << " ===" << std::endl;
}

LogMessage::LogMessage(const char* file, int line) {
    *this << '[' << file << ':' << line << "] ";
}

LogMessage::~LogMessage() { Logging::Get().writeLineRaw(str()); }

StderrLogMessage::StderrLogMessage(const char* file, int line)
    : log_(file, line) {}

StderrLogMessage::~StderrLogMessage() {
    std::cerr << str() << std::endl;
    log_ << str();
}