/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_MAINWINDOW_HPP_
#define INCLUDE_UI_MAINWINDOW_HPP_

#include <include/ui/CourseView.hpp>
#include <include/ui/LoginPanel.hpp>
#include <include/ui/InfoGrid.hpp>
#include <include/ui/FeedbackPanel.hpp>
#include <include/types/Course.hpp>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <string>
#include <vector>

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = nullptr);
  QWidget *centralWidget;
  LoginPanel *loginPanel;
  void viewFeedbackPanel();
  void viewGridPanel();
  void viewCourse(Course *course);

 private:
  QGridLayout *centralLayout;
  InfoGrid *infogrid;
  FeedbackPanel *feedbackPanel;
  QWidget *currentBodyWidget;
  std::vector<Course *> classes;
  std::vector<CourseView *> courseViews;
};

#endif  // INCLUDE_UI_MAINWINDOW_HPP_
