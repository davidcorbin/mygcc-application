/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Course.hpp>
#include <QDebug>
#include <QJsonArray>
#include <string>
#include <vector>

Course::Course(std::string *name,
               std::string *code,
               std::string *title,
               float credits) : name(name),
                                code(code),
                                title(title),
                                credits(credits) {
  homework = new std::vector<Assignment *>();
  students = new std::vector<Student *>();
  location = new std::vector<std::string *>();
  professor = new std::vector<std::string *>();
  times = new std::vector<ClassTime>();
}

Course::Course(QJsonObject jsonObject) {
  // Initialize empty objects
  homework = new std::vector<Assignment *>();
  students = new std::vector<Student *>();
  location = new std::vector<std::string *>();
  professor = new std::vector<std::string *>();
  times = new std::vector<ClassTime>();

  // Get data from json object
  name = new std::string(jsonObject["name"].toString().toStdString());
  code = new std::string(jsonObject["course"].toString().toStdString());
  title = new std::string(jsonObject["title"].toString().toStdString());
  credits = jsonObject["credits"].toDouble();

  // Parse location from json object
  if (jsonObject["location"].isArray()) {
    auto locationObj = jsonObject["location"].toArray();
    QJsonArray::iterator it;
    for (it = locationObj.begin(); it != locationObj.end(); it++) {
      auto locationStr = it->toString();
      location->push_back(new std::string(locationStr.toStdString()));
    }
  }

  // Parse professor from json object
  if (jsonObject["professor"].isArray()) {
    auto obj = jsonObject["professor"].toArray();
    QJsonArray::iterator it;
    for (it = obj.begin(); it != obj.end(); it++) {
      auto profStr = it->toString();
      professor->push_back(new std::string(profStr.toStdString()));
    }
  }

  // Parse class times from json object
  if (jsonObject["times"].isArray()) {
    auto obj = jsonObject["times"].toArray();
    QJsonArray::iterator it;
    for (it = obj.begin(); it != obj.end(); it++) {
      auto timeObj = it->toObject();
      auto *dow = new std::string(timeObj["day"].toString().toStdString());
      auto *start = new std::string(timeObj["start"].toString().toStdString());
      auto *end = new std::string(timeObj["end"].toString().toStdString());
      auto *classTime = new ClassTime(dow, start, end);
      times->push_back(*classTime);
    }
  }
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

std::string *Course::getTitle() const {
  return title;
}

void Course::setTitle(std::string *title) {
  Course::title = title;
}

double Course::getCredits() const {
  return credits;
}

void Course::setCredits(double credits) {
  Course::credits = credits;
}

std::vector<std::string *> *Course::getLocation() const {
  return location;
}

void Course::setLocation(std::vector<std::string *> *location) {
  Course::location = location;
}

std::vector<std::string *> *Course::getProfessor() const {
  return professor;
}

void Course::setProfessor(std::vector<std::string *> *professor) {
  Course::professor = professor;
}

std::vector<ClassTime> *Course::getTimes() const {
  return times;
}

void Course::setTimes(std::vector<ClassTime> *times) {
  Course::times = times;
}
