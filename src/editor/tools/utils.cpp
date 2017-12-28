/**
 * @file utils.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 20 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#include "../../editor/tools/utils.hpp"

#include <cstddef>
#include <iostream>

std::string trim(std::string const& str)
{
  if (str.empty())
    return str;

  std::size_t firstScan = str.find_first_not_of(' ');
  std::size_t first = firstScan == std::string::npos ? str.length() : firstScan;
  std::size_t last = str.find_last_not_of(' ');
  return str.substr(first, last - first + 1);
}

void printLog(std::string const & log, LogType logT)
{
  if (logT == LogType::ERROR)
  {
    std::cerr << "\033[1;" << (int)logT << 'm' << logT << log << "\033[0m" << '\n';
  }
  else
  {
    std::cout << "\033[0;" << (int)logT << 'm' << logT << log << "\033[0m" << '\n';
  }
}

std::ostream& operator <<(std::ostream& output, LogType const & var)
{
  switch (var) {
  case LogType::DEBUG:
    return output << "Debug : ";
  case LogType::ERROR:
    return output << "Error : ";
  case LogType::INFO:
    return output << "Info : ";
  case LogType::OK:
    return output << "Ok : ";
  case LogType::WARNING:
    return output << "Warning : ";
  }
  return output;

}
