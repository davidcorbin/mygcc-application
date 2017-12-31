/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_FILENOTFOUND_HPP_
#define INCLUDE_FILENOTFOUND_HPP_


#include <string>

class FileNotFound {
 private:
  std::string m_error;

 public:
  explicit FileNotFound(const std::string *error): m_error(*error) {}
  const char* getError() { return m_error.c_str(); }
};


#endif  // INCLUDE_FILENOTFOUND_HPP_
