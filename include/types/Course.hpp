/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_COURSE_HPP_
#define INCLUDE_TYPES_COURSE_HPP_


#include <string>

class Course {
 public:
  Course(const std::string &name, const std::string &code);
  const std::string &getName() const;
  const std::string &getCode() const;

 private:
  std::string name;
  std::string code;
};

#endif  // INCLUDE_TYPES_COURSE_HPP_
