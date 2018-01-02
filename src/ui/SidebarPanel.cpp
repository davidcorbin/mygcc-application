/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/Color.hpp>
#include <include/ui/SidebarPanel.hpp>
#include <include/ui/SidebarListItem.hpp>

#include <vector>

SidebarPanel::SidebarPanel(std::vector<Course *> *courses) :
    courses(*courses) {
}

void SidebarPanel::setup() {
  sidebarItemLayout = new QVBoxLayout;

  for (auto course : courses) {
    auto item = new SidebarListItem(course);
    item->setup();
    sidebarItemLayout->addWidget(item);
  }

  // Add stretching below last item
  sidebarItemLayout->addStretch();

  setPalette(Color::bg_primary());
  setLayout(sidebarItemLayout);
}
