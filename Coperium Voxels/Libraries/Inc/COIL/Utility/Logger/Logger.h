#pragma once
#ifndef COIL_LOG_FILE_H
#define COIL_LOG_FILE_H

// --------------------------------- External Includes
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>

// --------------------------------- Internal Includes
#include "../Types.h"
#include "../Constants.h"

namespace Coil {
class Logger {
public:
    static void init_logger(log_style_t style = log_style_t::LOG_TO_FILE, const std::string& file_name = "Coil_Engine.log");

    static void log(const std::string& caller, const std::string& message);

private:
    static log_style_t log_style;
    static std::string log_file_name;

    static void log_to_file(const std::string& caller, const std::string& message);
    static void log_to_console(const std::string& caller, const std::string& message);
    static std::string format_message(const std::string& caller, const std::string& message);
    static std::string get_current_date_time();
};

} // namespace Coil

#endif // !COIL_LOG_FILE_H
