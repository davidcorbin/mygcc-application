/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Course.hpp>

#include <string>

Course::Course(const std::string &name, const std::string &code) : name(name),
                                                                   code(code) {
}

const std::string &Course::getName() const {
  return name;
}

const std::string &Course::getCode() const {
  return code;
}
