#pragma once

#include <fstream>
#include <sstream>
#include <string>

class Logging {
public:
    static Logging& Get();

    // Sets the name of the log. Empty name disables logging.
    void setFilename(const std::string& filename);

private:
    void writeLineRaw(const std::string& line);

    std::string filename_;
    std::ofstream file_;

    Logging() = default;
    friend class LogMessage;
};

class LogMessage : public std::ostringstream {
public:
    LogMessage(const char* file, int line);
    ~LogMessage();
};

class StderrLogMessage : public std::ostringstream {
public:
    StderrLogMessage(const char* file, int line);
    ~StderrLogMessage();

private:
    LogMessage log_;
};

#define LOGFILE LogMessage(__FILE__, __LINE__)
#define CERR StderrLogMessage(__FILE__, __LINE__)