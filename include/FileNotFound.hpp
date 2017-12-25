/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_FILENOTFOUND_HPP
#define FACADE_APPLICATION_FILENOTFOUND_HPP


#include <string>

class FileNotFound {
private:
  std::string m_error;

public:
  explicit FileNotFound(const std::string *error): m_error(*error) {}
  const char* getError() { return m_error.c_str(); }
};


#endif //FACADE_APPLICATION_FILENOTFOUND_HPP
