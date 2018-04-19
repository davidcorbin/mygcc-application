/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_CLASSROOMVIEW_HPP_
#define INCLUDE_UI_CLASSROOMVIEW_HPP_

#include <include/types/Course.hpp>
#include <include/ui/ClassroomViewItem.hpp>
#include <QWidget>
#include <QGridLayout>
#include <string>
#include <vector>

class ClassroomView : public QWidget {
  Q_OBJECT

 public:
  explicit ClassroomView(Course *course);
  void setup();

 private:
  Course *course;
  QGridLayout *grid;
  std::vector<ClassroomViewItem*> *classroomViewItems;

 private slots:  // NOLINT
  void updatePhoto(std::string *filename);
};

#endif  // INCLUDE_UI_CLASSROOMVIEW_HPP_
