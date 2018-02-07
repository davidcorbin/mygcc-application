/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/ClassroomView.hpp>
#include <vector>

ClassroomView::ClassroomView(Course *course) : course(course) {
  grid = new QGridLayout;
  grid->setAlignment(Qt::AlignTop);
  classroomViewItems = new std::vector<ClassroomViewItem*>();
}

void ClassroomView::setup() {
  auto *students = course->getStudents();
  for (auto *student : *students) {
    auto *classroomViewItem = new ClassroomViewItem(student);
    classroomViewItem->setup();
    grid->addWidget(classroomViewItem,
                    classroomViewItems->size()/3,
                    classroomViewItems->size()%3);
    classroomViewItems->push_back(classroomViewItem);
  }
  setLayout(grid);
}
