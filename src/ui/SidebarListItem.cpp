/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/SidebarListItem.hpp>
#include <include/ui/Color.hpp>
#include <string>

SidebarListItem::SidebarListItem(const Course *course) : course(course) {
  label = new SidebarLabel(course->getName().c_str());
  icon = new SidebarIcon(new std::string("home"));
}

void SidebarListItem::setup() {
  label->setup();
  QPixmap iconmap = icon->setup();
  image_label = new QLabel();
  image_label->setPixmap(iconmap);
  image_label->setFixedWidth(22);

  layout = new QGridLayout;
  layout->addWidget(image_label, 0, 0);
  layout->addWidget(label, 0, 1);
  setLayout(layout);
}

void SidebarListItem::enterEvent(QEvent* event) {
  label->setPalette(Color::text_primary());
  image_label->setPixmap(icon->active);
}

void SidebarListItem::leaveEvent(QEvent* event) {
  label->setPalette(Color::text_secondary());
  image_label->setPixmap(icon->normal);
}
