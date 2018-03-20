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
  /**
   * Constructor that sets login.
   * @param login login object
   */
  explicit Homework(Login *login);

  /**
   * Constructor without login.
   */
  Homework();

  /**
   * Get homework assignments/exam information.
   * @param token API token
   * @param courseCode course code string e.g. "BIOL 101 A"
   */
  void getHomework(std::string *token, std::string *courseCode);

  /**
   * Get assignments.
   * @return std::vector of assignments
   */
  std::vector<Assignment *> *getAssignments() const;

  /**
   * Get login object.
   * @return login object
   */
  Login *getLogin() const;

  /**
   * Set login object.
   * @param login login object
   */
  void setLogin(Login *login);

 private:
  bool homeworkRec;
  std::vector<Assignment *> *assignments;
  Login *login;
  std::string *courseCode;

  void parseHomeworkJson(QJsonObject object);
  void sortAssignments();

 signals:  // NOLINT
  /**
   * Signal that the homework has been received from mygcc and parsed.
   */
  void homeworkReceived();
};

#endif  // INCLUDE_DATA_HOMEWORK_HPP_
