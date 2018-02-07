/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/CourseView.hpp>
#include <include/ui/CourseAssignmentItem.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>
#include <QNetworkRequest>
#include <iostream>

CourseView::CourseView(Course *course, int min_width) : course(course) {
  setMinimumWidth(min_width);
  tabBodyLayout = new QVBoxLayout;
  tabBar = new QTabBar;
  assignmentScrollArea = new QScrollArea;
  fileViewArea = new QScrollArea;
  classroomViewArea = new QScrollArea;
  classroomView = new ClassroomView(course);
}

void CourseView::setup() {
  setupTabBar();
  setupAssignmentView();
  setupFileView();
  setupClassroomView();

  tabBodyLayout->addWidget(tabBar);
  tabBodyLayout->addWidget(assignmentScrollArea);
  tabBodyLayout->addWidget(fileViewArea);
  tabBodyLayout->addWidget(classroomViewArea);
  currentWidget = assignmentScrollArea;
  tabBodyLayout->setAlignment(tabBar, Qt::AlignTop);

  // Call tabBarClicked() when tab bar item is clicked
  connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(tabBarClicked()));

  setStyleSheet("border-radius:5px;");
  setLayout(tabBodyLayout);
}

void CourseView::setupTabBar() {
  tabBar->addTab("Assignments");
  tabBar->addTab("Files");
  tabBar->addTab("People");
}

void CourseView::setupAssignmentView() {
  auto *cont = new QWidget;

  auto *assignmentLayout = new QVBoxLayout(cont);
  assignmentLayout->setContentsMargins(0, 0, 0, 0);
  assignmentLayout->setAlignment(Qt::AlignTop);

  auto *assignments = course->getAssignments();
  for (auto *assignment : *assignments) {
    auto *assignmentItem = new CourseAssignmentItem(assignment);
    assignmentItem->setup();
    assignmentLayout->addWidget(assignmentItem);
  }

  // If no assignments show a label that tells the user there are no assignments
  if (course->getAssignments()->empty()) {
    auto *emptyLabel = new QLabel("No assignments yet");
    emptyLabel->setFont(Font::assignmentName());
    emptyLabel->setPalette(Color::text_primary());
    emptyLabel->setAlignment(Qt::AlignCenter);
    assignmentLayout->addWidget(emptyLabel);
    assignmentLayout->setAlignment(Qt::AlignVCenter);
  }

  assignmentScrollArea->setWidget(cont);
  assignmentScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  assignmentScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  assignmentScrollArea->setStyleSheet("border: none; padding: 0px;");
  assignmentScrollArea->setContentsMargins(0, 0, 0, 0);
  assignmentScrollArea->setWidgetResizable(true);
  assignmentScrollArea->setAlignment(Qt::AlignLeading|
                                         Qt::AlignLeft|Qt::AlignTop);
}

void CourseView::setupFileView() {
  fileViewArea->setWidget(new QLabel("files..."));
  fileViewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  fileViewArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  fileViewArea->setStyleSheet("border: none; padding: 0px;");
  fileViewArea->setContentsMargins(0, 0, 0, 0);
  fileViewArea->setWidgetResizable(true);
  fileViewArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
  fileViewArea->hide();
}

void CourseView::setupClassroomView() {
  classroomView->setup();
  classroomViewArea->setWidget(classroomView);
  classroomViewArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  classroomViewArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  classroomViewArea->setStyleSheet("border: none; padding: 0px;");
  classroomViewArea->setContentsMargins(0, 0, 0, 0);
  classroomViewArea->setWidgetResizable(true);
  classroomViewArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
  classroomViewArea->hide();
}

void CourseView::tabBarClicked() {
  int selectedTabIndex = tabBar->currentIndex();
  currentWidget->hide();
  switch (selectedTabIndex) {
    case 0:
      assignmentScrollArea->show();
      currentWidget = assignmentScrollArea;
      break;
    case 1:
      fileViewArea->show();
      currentWidget = fileViewArea;
      break;
    case 2:
      classroomViewArea->show();
      currentWidget = classroomViewArea;
      break;
  }
}
