/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_CLASS_HPP
#define FACADE_APPLICATION_CLASS_HPP


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


#endif //FACADE_APPLICATION_CLASS_HPP
