/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/Color.hpp>
#include <include/ui/SidebarPanel.hpp>
#include <include/ui/Font.hpp>

#include <vector>

SidebarPanel::SidebarPanel(std::vector<Course *> *courses) :
    courses(*courses) {
}

void SidebarPanel::setup() {
  sidebarItemLayout = new QVBoxLayout;

  for (auto course : courses) {
    auto label = new QLabel(course->getName().c_str());
    label->setContentsMargins(20, 3, 5, 3);
    label->setPalette(Color::text_secondary());
    label->setFont(Font::sidebarItem());
    sidebarItemLayout->addWidget(label);
  }

  // Add stretching below last item
  sidebarItemLayout->addStretch();

  setPalette(Color::bg_primary());
  setLayout(sidebarItemLayout);
}
