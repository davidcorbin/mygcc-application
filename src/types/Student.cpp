/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Student.hpp>
#include <string>

Student::Student(std::string *imageUrl,
                 bool isFaculty,
                 std::string *name,
                 int id) : imageUrl(imageUrl),
                           isFaculty(isFaculty),
                           name(name),
                           id(id) {}

std::string *Student::getImageUrl() const {
  return imageUrl;
}

void Student::setImageUrl(std::string *imageUrl) {
  Student::imageUrl = imageUrl;
}

bool Student::isIsFaculty() const {
  return isFaculty;
}

void Student::setIsFaculty(bool isFaculty) {
  Student::isFaculty = isFaculty;
}

std::string *Student::getName() const {
  return name;
}

void Student::setName(std::string *name) {
  Student::name = name;
}

int Student::getId() const {
  return id;
}

void Student::setId(int id) {
  Student::id = id;
}
