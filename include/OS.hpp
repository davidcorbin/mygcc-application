/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_OS_HPP_
#define INCLUDE_OS_HPP_


#include <string>

class OS {
 public:
  static std::string getOSName();
  static std::string* appVersion();
};

#endif  // INCLUDE_OS_HPP_
