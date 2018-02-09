/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Course.hpp>
#include <string>
#include <vector>

Course::Course(std::string *name, std::string *code) : name(name),
                                                       code(code) {
  homework = new std::vector<Assignment *>();
  students = new std::vector<Student *>();
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

void Course::addStudent(Student *student) {
  students->push_back(student);
}

std::vector<Student *>* Course::getStudents() {
  return students;
}

std::vector<NetworkFile *> *Course::getFiles() const {
  return files;
}

void Course::setFiles(std::vector<NetworkFile *> *files) {
  Course::files = files;
}
