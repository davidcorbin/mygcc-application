/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_DATA_SCHEDULE_HPP_
#define INCLUDE_DATA_SCHEDULE_HPP_

#include <include/data/Login.hpp>
#include <include/types/Course.hpp>
#include <string>
#include <vector>

class Schedule : public QObject {
  Q_OBJECT

 public:
  explicit Schedule(Login *login);
  void getSchedule(std::string *token);
  std::vector<Course *> *getCourses() const;
  void setCourses(std::vector<Course *> *courses);
  bool isScheduleRetrieved() const;
  void setScheduleRetrieved(bool scheduleRetrieved);

 private:
  Login *login;
  std::vector<Course *> *courses;
  bool scheduleRetrieved;

  void parseScheduleJson(QJsonArray array);

 private slots:  // NOLINT
  void queueGetSchedule();

 signals:  // NOLINT
  void scheduleReceived();

  // Sent after courses have been parsed into Course object
  void coursesLoaded();
};

#endif  // INCLUDE_DATA_SCHEDULE_HPP_
