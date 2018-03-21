/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_COURSEASSIGNMENTITEM_HPP_
#define INCLUDE_UI_COURSEASSIGNMENTITEM_HPP_

#include <include/types/Course.hpp>
#include <QWidget>
#include <QLabel>
#include <string>

class CourseAssignmentItem : public QWidget {
 public:
  explicit CourseAssignmentItem(Assignment *assignment);
  void setup();

 private:
  QLabel* setupLetterLabel(QString *letterStr);
  QLabel* setupGradeLabel(QString *gradeStr);
  QLabel* setupNameLabel(QString *nameStr);
  QLabel* setupDueDateLabel(QString *dueDateStr);
  std::string getPointsString();
  std::string getReadablePoints(double points);
  QPalette letterColor(QString *letterStr);
  Assignment *assignment;
};

#endif  // INCLUDE_UI_COURSEASSIGNMENTITEM_HPP_
