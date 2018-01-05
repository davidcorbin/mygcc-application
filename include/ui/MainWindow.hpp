/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_MAINWINDOW_HPP_
#define INCLUDE_UI_MAINWINDOW_HPP_

#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <string>

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget *parent = nullptr);
  void setTestText(std::string text);

 private:
  QLabel *testlabel;
  QHBoxLayout *qhblayout;
  QWidget *mainBody;
  QGridLayout *centralLayout;
  QWidget *centralWidget;
};

#endif  // INCLUDE_UI_MAINWINDOW_HPP_
