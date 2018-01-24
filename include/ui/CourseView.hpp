/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_COURSEVIEW_HPP_
#define INCLUDE_UI_COURSEVIEW_HPP_

#include <include/types/Course.hpp>
#include <QWidget>
#include <QVBoxLayout>
#include <QTabBar>

class CourseView : public QWidget {
  Q_OBJECT

 public:
  explicit CourseView(Course *course);
  void setup();

  Course *course;

 private:
  QVBoxLayout *tabBodyLayout;
  QTabBar *tabBar;

 private slots:  // NOLINT
  void tabBarClicked();
};

#endif  // INCLUDE_UI_COURSEVIEW_HPP_
