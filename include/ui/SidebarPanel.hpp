/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_SIDEBARPANEL_HPP
#define FACADE_APPLICATION_SIDEBARPANEL_HPP

#include <include/types/Course.hpp>

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class SidebarPanel : public QWidget {
public:
  explicit SidebarPanel(std::vector<Course *> *courses);
  void setup();

private:
  QVBoxLayout *sidebarItemLayout;

  std::vector<Course *> courses;
};


#endif //FACADE_APPLICATION_SIDEBARPANEL_HPP
