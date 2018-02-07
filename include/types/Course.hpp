/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_COURSE_HPP_
#define INCLUDE_TYPES_COURSE_HPP_

#include <include/types/Assignment.hpp>
#include <include/types/Student.hpp>
#include <string>
#include <vector>

class Course {
 public:
  Course(std::string *name, std::string *code);
  std::string* getName();
  std::string* getCode();
  void addAssignment(Assignment *assignment);
  std::vector<Assignment *>* getAssignments();
  void addStudent(Student *student);
  std::vector<Student *>* getStudents();

 private:
  std::string *name;
  std::string *code;
  std::vector<Assignment *> *homework;
  std::vector<Student *> *students;
};

#endif  // INCLUDE_TYPES_COURSE_HPP_
