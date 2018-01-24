/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Course.hpp>
#include <string>
#include <vector>

Course::Course(std::string *name, std::string *code) : name(name),
                                                       code(code) {
}

std::string* Course::getName() {
  return name;
}

std::string* Course::getCode() {
  return code;
}

std::vector<Assignment *>* Course::getAssignments() {
  return homework;
}
