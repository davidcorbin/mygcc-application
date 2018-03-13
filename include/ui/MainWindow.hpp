/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_MAINWINDOW_HPP_
#define INCLUDE_UI_MAINWINDOW_HPP_

#include <include/api/JavaIntegration.hpp>
#include <include/ui/CourseView.hpp>
#include <include/ui/LoginPanel.hpp>
#include <include/ui/InfoGrid.hpp>
#include <include/ui/FeedbackPanel.hpp>
#include <include/types/Course.hpp>
#include <include/data/Schedule.hpp>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <string>
#include <vector>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(JavaIntegration *ji, Login *login, Schedule *schedule);
  QWidget *centralWidget;
  LoginPanel *loginPanel;
  void viewFeedbackPanel();
  void viewGridPanel();
  void viewCourse(Course *course);
  void closeEvent(QCloseEvent *event) override;

 protected:
  void showEvent(QShowEvent* event) override;

 private:
  QGridLayout *centralLayout;
  InfoGrid *infogrid;
  FeedbackPanel *feedbackPanel;
  QWidget *currentBodyWidget;
  std::vector<CourseView *> courseViews;

  // Java process
  JavaIntegration *javaIntegration;

  // Login object
  Login *login;

  // Schedule object
  Schedule *schedule;

 private slots:  // NOLINT
  void scheduleLoaded();
};

#endif  // INCLUDE_UI_MAINWINDOW_HPP_
