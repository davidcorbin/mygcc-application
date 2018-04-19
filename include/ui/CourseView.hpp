/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_COURSEVIEW_HPP_
#define INCLUDE_UI_COURSEVIEW_HPP_

#include <include/types/Course.hpp>
#include <include/ui/ClassroomView.hpp>
#include <QWidget>
#include <QVBoxLayout>
#include <QTabBar>
#include <QScrollArea>

class CourseView : public QWidget {
  Q_OBJECT

 public:
  explicit CourseView(Course *course, int min_width);
  void setup();

  Course *course;

 private:
  QVBoxLayout *tabBodyLayout;
  QTabBar *tabBar;
  QWidget *currentWidget;
  QScrollArea *assignmentScrollArea;
  QScrollArea *fileViewArea;
  QScrollArea *classroomViewArea;
  ClassroomView *classroomView;

  void setupTabBar();

 private slots:  // NOLINT
  void tabBarClicked();
  void setupAssignmentView();
  void setupFileView();
  void setupClassroomView();
};

#endif  // INCLUDE_UI_COURSEVIEW_HPP_
