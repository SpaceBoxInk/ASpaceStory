/**
 * @file utils.hpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 20 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include <string>

enum class LogType
{
  OK = 32,
  INFO = 36,
  WARNING = 33,
  ERROR = 91,
  DEBUG = 5,
};

std::ostream& operator<<(std::ostream& output, LogType const& var);

std::string trim(std::string const& str);
void printLog(std::string const& log, LogType logT = LogType::DEBUG);
