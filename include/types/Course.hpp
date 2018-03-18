/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_COURSE_HPP_
#define INCLUDE_TYPES_COURSE_HPP_

#include <include/types/Assignment.hpp>
#include <include/types/Student.hpp>
#include <include/types/NetworkFile.hpp>
#include <include/types/ClassTime.hpp>
#include <include/data/Homework.hpp>
#include <QJsonObject>
#include <string>
#include <vector>

class Course {
 public:
  Course(std::string *name,
         std::string *code,
         std::string *title,
         float credits);
  explicit Course(QJsonObject jsonObject);
  std::string* getName();
  std::string* getCourseCode();
  void addStudent(Student *student);
  std::vector<Student *>* getStudents();
  std::vector<NetworkFile *> *getFiles() const;
  void setFiles(std::vector<NetworkFile *> *files);
  std::string *getTitle() const;
  void setTitle(std::string *title);
  double getCredits() const;
  void setCredits(double credits);
  std::vector<std::string *> *getLocation() const;
  void setLocation(std::vector<std::string *> *location);
  std::vector<std::string *> *getProfessor() const;
  void setProfessor(std::vector<std::string *> *professor);
  std::vector<ClassTime> *getTimes() const;
  void setTimes(std::vector<ClassTime> *times);
  Homework *getHomeworkObj() const;
  void setHomeworkObj(Homework *homeworkObj);
  std::string *getCourseCodeWithSpaces() const;
  void setCourseCodeWithSpaces(std::string *courseCodeWithSpaces);

  void loadHomework(Login *login);

 private:
  std::string *name;
  std::string *courseCode;
  std::string *courseCodeWithSpaces;
  std::string *title;
  double credits;
  std::vector<std::string *> *location;
  std::vector<std::string *> *professor;
  std::vector<ClassTime> *times;
  std::vector<Student *> *students;
  std::vector<NetworkFile *> *files;
  Homework *homeworkObj;
};

#endif  // INCLUDE_TYPES_COURSE_HPP_
