/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_SIDEBARLISTITEM_HPP_
#define INCLUDE_UI_SIDEBARLISTITEM_HPP_

#include <include/types/Course.hpp>
#include <include/ui/SidebarLabel.hpp>
#include <include/ui/SidebarIcon.hpp>
#include <QWidget>
#include <QVBoxLayout>

class SidebarListItem : public QWidget {
 public:
  explicit SidebarListItem(const Course *course);
  void setup();

 private:
  const Course *course;
  SidebarLabel *label;
  SidebarIcon *icon;
  QGridLayout *layout;
  QLabel *image_label;

  void enterEvent(QEvent* event) override;
  void leaveEvent(QEvent* event) override;
};


#endif  // INCLUDE_UI_SIDEBARLISTITEM_HPP_
