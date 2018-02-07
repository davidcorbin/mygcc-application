/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_STUDENT_HPP_
#define INCLUDE_TYPES_STUDENT_HPP_

#include <string>

class Student {
 public:
  Student(std::string *imageUrl, bool isFaculty, std::string *name, int id);
  std::string *getImageUrl() const;
  void setImageUrl(std::string *imageUrl);
  bool isIsFaculty() const;
  void setIsFaculty(bool isFaculty);
  std::string *getName() const;
  void setName(std::string *name);
  int getId() const;
  void setId(int id);

 private:
  std::string *imageUrl;
  bool isFaculty;
  std::string *name;
  int id;
};

#endif  // INCLUDE_TYPES_STUDENT_HPP_
