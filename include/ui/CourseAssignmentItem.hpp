/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_COURSEASSIGNMENTITEM_HPP_
#define INCLUDE_UI_COURSEASSIGNMENTITEM_HPP_

#include <include/types/Course.hpp>
#include <QWidget>
#include <QLabel>

class CourseAssignmentItem : public QWidget {
 public:
  explicit CourseAssignmentItem(Course *course);
  void setup();

 private:
  QLabel* setupLetterLabel(QString *letterStr);
  QLabel* setupGradeLabel(QString *gradeStr);
  QLabel* setupNameLabel(QString *nameStr);
  QLabel* setupDueDateLabel(QString *dueDateStr);
  Course *course;
};

#endif  // INCLUDE_UI_COURSEASSIGNMENTITEM_HPP_
