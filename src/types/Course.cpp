/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Course.hpp>
#include <string>
#include <vector>

Course::Course(std::string *name,
               std::string *code,
               std::string *title,
               float credits) : name(name),
                                courseCode(code),
                                title(title),
                                credits(credits) {
  students = new std::vector<Student *>();
  location = new std::vector<std::string *>();
  professor = new std::vector<std::string *>();
  times = new std::vector<ClassTime>();
  homeworkObj = new Homework();
  classmateObj = new Classmate();
}

Course::Course(QJsonObject jsonObject) {
  // Initialize empty objects
  students = new std::vector<Student *>();
  location = new std::vector<std::string *>();
  professor = new std::vector<std::string *>();
  times = new std::vector<ClassTime>();

  // Get data from json object
  name = new std::string(jsonObject["name"].toString().toStdString());
  courseCode = new std::string(jsonObject["code"].toString().toStdString());
  courseCodeWithSpaces = new std::string(jsonObject["course"]
                                             .toString().toStdString());
  title = new std::string(jsonObject["title"].toString().toStdString());
  credits = jsonObject["credits"].toDouble();

  // Parse location from json object
  if (jsonObject["location"].isArray()) {
    auto locationObj = jsonObject["location"].toArray();
    foreach(const QJsonValue & value, locationObj) {
      std::string locationStr = value.toString().toStdString();
      location->push_back(new std::string(locationStr));
    }
  }

  // Parse professor from json object
  if (jsonObject["professor"].isArray()) {
    auto obj = jsonObject["professor"].toArray();
    foreach(const QJsonValue & value, obj) {
      std::string profStr = value.toString().toStdString();
      professor->push_back(new std::string(profStr));
    }
  }

  // Parse class times from json object
  if (jsonObject["times"].isArray()) {
    auto obj = jsonObject["times"].toArray();
    foreach(const QJsonValue & value, obj) {
      auto timeObj = value.toObject();
      auto *dow = new std::string(timeObj["day"].toString().toStdString());
      auto *start = new std::string(timeObj["start"].toString().toStdString());
      auto *end = new std::string(timeObj["end"].toString().toStdString());
      auto *classTime = new ClassTime(dow, start, end);
      times->push_back(*classTime);
    }
  }

  homeworkObj = new Homework();
  classmateObj = new Classmate();
}

std::string* Course::getName() {
  return name;
}

std::string* Course::getCourseCode() {
  return courseCode;
}

void Course::loadStudents(Login *login) {
  classmateObj->setLogin(login);
  classmateObj->loadClassmates(login->getApiToken(), courseCode);
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

void Course::loadHomework(Login *login) {
  homeworkObj->setLogin(login);
  homeworkObj->getHomework(login->getApiToken(), courseCode);
}

Homework *Course::getHomeworkObj() const {
  return homeworkObj;
}

void Course::setHomeworkObj(Homework *homeworkObj) {
  Course::homeworkObj = homeworkObj;
}

Classmate *Course::getClassMateObj() const {
  return classmateObj;
}

void Course::setClassmateObj(Classmate *classmateObj) {
  Course::classmateObj = classmateObj;
}

std::string *Course::getCourseCodeWithSpaces() const {
  return courseCodeWithSpaces;
}

void Course::setCourseCodeWithSpaces(std::string *courseCodeWithSpaces) {
  Course::courseCodeWithSpaces = courseCodeWithSpaces;
}
