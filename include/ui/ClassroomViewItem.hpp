/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_CLASSROOMVIEWITEM_HPP_
#define INCLUDE_UI_CLASSROOMVIEWITEM_HPP_

#include <include/types/Student.hpp>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class ClassroomViewItem : public QWidget {
 public:
  explicit ClassroomViewItem(Student *student);
  void setup();

 private:
  Student *student;
  QVBoxLayout *verticalLayout;
  QPixmap defImage;
  QLabel *imageLabel;
  QLabel *nameLabel;
};

#endif  // INCLUDE_UI_CLASSROOMVIEWITEM_HPP_