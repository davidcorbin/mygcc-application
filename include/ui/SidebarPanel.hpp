/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_SIDEBARPANEL_HPP_
#define INCLUDE_UI_SIDEBARPANEL_HPP_

#include <include/types/Course.hpp>

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include <vector>

class SidebarPanel : public QWidget {
 public:
  explicit SidebarPanel(std::vector<Course *> *courses);
  void setup();

 private:
  QVBoxLayout *sidebarItemLayout;
  std::vector<Course *> courses;
};


#endif  // INCLUDE_UI_SIDEBARPANEL_HPP_
