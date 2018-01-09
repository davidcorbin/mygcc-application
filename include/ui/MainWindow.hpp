/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_MAINWINDOW_HPP_
#define INCLUDE_UI_MAINWINDOW_HPP_

#include <include/ui/LoginPanel.hpp>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <string>

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = nullptr);
  void setTestText(std::string text);
  QWidget *centralWidget;
  LoginPanel *loginPanel;

 private:
  QLabel *testlabel;
  QHBoxLayout *qhblayout;
  QWidget *mainBody;
  QGridLayout *centralLayout;
};

#endif  // INCLUDE_UI_MAINWINDOW_HPP_
