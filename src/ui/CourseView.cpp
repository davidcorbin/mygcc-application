/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/CourseView.hpp>
#include <include/ui/CourseAssignmentItem.hpp>
#include <QScrollArea>
#include <QLabel>

CourseView::CourseView(Course *course) : course(course) {
  tabBodyLayout = new QVBoxLayout;
  tabBar = new QTabBar;
}

void CourseView::setup() {
  tabBar->addTab("Assignments");
  tabBar->addTab("Files");
  tabBar->addTab("People");

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

  auto *scrollArea = new QScrollArea;
  scrollArea->setWidget(cont);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setStyleSheet("border: none; padding: 0px;");
  scrollArea->setContentsMargins(0, 0, 0, 0);
  scrollArea->setWidgetResizable(true);
  scrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

  tabBodyLayout->addWidget(tabBar);
  tabBodyLayout->addWidget(scrollArea);
  tabBodyLayout->setAlignment(tabBar, Qt::AlignTop);

  // Call tabBarClicked() when tab bar item is clicked
  connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(tabBarClicked()));

  setStyleSheet("border-radius:5px;");
  setLayout(tabBodyLayout);
}

void CourseView::tabBarClicked() {
  int selectedTabIndex = tabBar->currentIndex();
}
