/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_SIDEBARLABEL_HPP_
#define INCLUDE_UI_SIDEBARLABEL_HPP_

#include <QLabel>

class SidebarLabel : public QLabel {
 public:
  explicit SidebarLabel(const QString text) : QLabel(text) {}
  void setup();
};

#endif  // INCLUDE_UI_SIDEBARLABEL_HPP_
