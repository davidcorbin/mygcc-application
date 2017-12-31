/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_MAINWINDOW_HPP_
#define INCLUDE_UI_MAINWINDOW_HPP_

#include <QMainWindow>

class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
};

#endif  // INCLUDE_UI_MAINWINDOW_HPP_
