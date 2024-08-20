#include "Logger.h"
#include <iostream>
#include <cstdio>

namespace Coil {

// Initialize static members
log_style_t Logger::log_style = log_style_t::LOG_TO_FILE;
std::string Logger::log_file_name = "Engine.log";

/* ============================================================================
 * --------------------------------- Initialize Logger
 * - Sets the logging style and file name
 * - Removes existing log file and writes an initialization message
 * ============================================================================
 */
void Logger::init_logger(log_style_t style, const std::string& file_name) {
    log_style = style;
    log_file_name = file_name;
    if (log_style == log_style_t::LOG_TO_FILE) {
        std::remove(log_file_name.c_str());
        std::ofstream log_file(log_file_name, std::ios_base::app);
        log_file
            << "-------------------------------------------\n"
            << "           " + get_current_date_time() << "\n"
            << "-------------------------------------------\n";
    }
}

/* ============================================================================
 * --------------------------------- Log Message
 * - Logs a message based on the current log style
 * ============================================================================
 */
void Logger::log(const std::string& caller, const std::string& message) {
    switch (log_style) {
    case log_style_t::LOG_TO_FILE:
        log_to_file(caller, message);
        break;
    case log_style_t::LOG_TO_CONSOLE:
        log_to_console(caller, message);
        break;
    case log_style_t::DISABLE_LOG:
        break;
    }
}

/* ============================================================================
 * --------------------------------- Format Message
 * - Formats the log message with the caller's name and message content
 * ============================================================================
 */
std::string Logger::format_message(const std::string& caller, const std::string& message) {
    std::ostringstream stream;
    stream << std::setw(LOG_CALLER_LENGTH)
        << std::left
        << std::setfill(' ')
        << caller;
    std::string formatted = stream.str();
    return formatted + " > " + message;
}

/* ============================================================================
 * --------------------------------- Get Current Date and Time
 * - Retrieves the current date and time as a formatted string
 * ============================================================================
 */
std::string Logger::get_current_date_time() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::tm time_info;
    localtime_s(&time_info, &now);
    std::strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &time_info);
    return std::string(buf);
}

/* ============================================================================
 * --------------------------------- Log to File
 * - Appends a formatted log message to the specified log file
 * ============================================================================
 */
void Logger::log_to_file(const std::string& caller, const std::string& message) {
    std::string log_entry = format_message(caller, message);
    std::ofstream log_file(log_file_name, std::ios_base::app);
    log_file << (log_entry + "\n");
}

/* ============================================================================
 * --------------------------------- Log to Console
 * - Outputs a formatted log message to the console
 * ============================================================================
 */
void Logger::log_to_console(const std::string& caller, const std::string& message) {
    std::string log_entry = format_message(caller, message);
    std::cout << log_entry << std::endl;
}

}
