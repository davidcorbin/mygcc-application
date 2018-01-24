/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_COURSE_HPP_
#define INCLUDE_TYPES_COURSE_HPP_

#include <include/types/Assignment.hpp>
#include <string>
#include <vector>

class Course {
 public:
  Course(std::string *name, std::string *code);
  std::string* getName();
  std::string* getCode();
  std::vector<Assignment *>* getAssignments();

 private:
  std::string *name;
  std::string *code;
  std::vector<Assignment *> *homework;
};

#endif  // INCLUDE_TYPES_COURSE_HPP_
