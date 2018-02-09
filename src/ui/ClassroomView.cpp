/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/ClassroomView.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>
#include <vector>

ClassroomView::ClassroomView(Course *course) : course(course) {
  grid = new QGridLayout;
  grid->setAlignment(Qt::AlignTop);
  classroomViewItems = new std::vector<ClassroomViewItem*>();
}

void ClassroomView::setup() {
  auto *students = course->getStudents();

  // If no students
  if (students->empty()) {
    auto *emptyLabel = new QLabel("No students could be retrieved");
    emptyLabel->setFont(Font::assignmentName());
    emptyLabel->setPalette(Color::text_primary());
    emptyLabel->setAlignment(Qt::AlignCenter);
    grid->addWidget(emptyLabel);
    grid->setAlignment(Qt::AlignVCenter);
  }

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
