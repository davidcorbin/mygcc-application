/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/SidebarListItem.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/SidebarPanel.hpp>
#include <QApplication>
#include <string>

SidebarListItem::SidebarListItem(Course *course) : course(course) {
  label = new SidebarLabel(course->getName()->c_str());
  icon = new SidebarIcon(course);
}

void SidebarListItem::setup() {
  label->setup();
  QPixmap iconmap = icon->setup();
  image_label = new QLabel();
  image_label->setPixmap(iconmap);
  image_label->setFixedWidth(22);
  currentState = NORMAL;

  layout = new QGridLayout;
  layout->addWidget(image_label, 0, 0);
  layout->addWidget(label, 0, 1);
  layout->setContentsMargins(10, 5, 10, 5);
  setLayout(layout);
}

void SidebarListItem::setNormal() {
  label->setPalette(Color::text_secondary());
  image_label->setPixmap(icon->normal);
  currentState = NORMAL;
}

void SidebarListItem::setActive() {
  label->setPalette(Color::text_primary());
  image_label->setPixmap(icon->active);
  currentState = ACTIVE;
}

void SidebarListItem::setSelected() {
  label->setPalette(Color::text_selected());
  image_label->setPixmap(icon->selected);
  currentState = SELECTED;
}

void SidebarListItem::enterEvent(QEvent* event) {
  if (currentState != SELECTED) {
    setActive();
  }
}

void SidebarListItem::leaveEvent(QEvent* event) {
  if (currentState != SELECTED) {
    setNormal();
  }
}

void SidebarListItem::mouseReleaseEvent(QMouseEvent *event) {
  reinterpret_cast<SidebarPanel*>(parentWidget())->setSelected(course);
}
