/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Course.hpp>
#include <string>
#include <vector>

Course::Course(std::string *name, std::string *code) : name(name),
                                                       code(code) {
  homework = new std::vector<Assignment *>();
}

std::string* Course::getName() {
  return name;
}

std::string* Course::getCode() {
  return code;
}

void Course::addAssignment(Assignment *assignment) {
  homework->push_back(assignment);
}

std::vector<Assignment *>* Course::getAssignments() {
  return homework;
}
