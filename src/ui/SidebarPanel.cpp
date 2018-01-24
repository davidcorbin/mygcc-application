/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/Color.hpp>
#include <include/ui/SidebarPanel.hpp>
#include <include/ui/MainWindow.hpp>
#include <string>
#include <vector>

SidebarPanel::SidebarPanel(std::vector<Course *> *courses) :
    courses(*courses) {
  listItems = new std::vector<SidebarListItem *>();
}

void SidebarPanel::setup() {
  sidebarItemLayout = new QVBoxLayout;

  // Home item
  auto home = new SidebarListItem(new Course(new std::string("Home"),
                                             new std::string("Home")));
  home->setup();
  sidebarItemLayout->addWidget(home);
  listItems->push_back(home);
  home->setSelected();

  for (auto course : courses) {
    auto item = new SidebarListItem(course);
    item->setup();
    sidebarItemLayout->addWidget(item);
    listItems->push_back(item);
  }

  // Add stretching below last item
  sidebarItemLayout->addStretch();

  setPalette(Color::bg_primary());
  setLayout(sidebarItemLayout);
}

// Sets selected course in sidebar.
void SidebarPanel::setSelected(Course *course) {
  selectedCourse = course;
  for (auto listItem : *listItems) {
    listItem->setNormal();
    if (listItem->course == course) {
      listItem->setSelected();
    }
  }

  auto *mainWindow = qobject_cast<MainWindow *>(
      parentWidget()->parentWidget()->parentWidget());
  if (*(course->getCode()) == "Home") {
    mainWindow->viewGridPanel();
  } else {
    mainWindow->viewCourse(course);
  }
}
