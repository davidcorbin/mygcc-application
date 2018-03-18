/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_DATA_HOMEWORK_HPP_
#define INCLUDE_DATA_HOMEWORK_HPP_

#include <include/data/Login.hpp>
#include <include/types/Assignment.hpp>
#include <string>
#include <vector>

class Homework : public QObject {
  Q_OBJECT

 public:
  explicit Homework(Login *login);
  Homework();
  void getHomework(std::string *token, std::string *courseCode);
  std::vector<Assignment *> *getAssignments() const;
  void setAssignments(std::vector<Assignment *> *assignments);
  Login *getLogin() const;
  void setLogin(Login *login);

 private:
  bool homeworkRec;
  std::vector<Assignment *> *assignments;
  Login *login;
  std::string *courseCode;

  void parseHomeworkJson(QJsonObject object);

 signals:  // NOLINT
  void homeworkReceived();
};


#endif  // INCLUDE_DATA_HOMEWORK_HPP_
