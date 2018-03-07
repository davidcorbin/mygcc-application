/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/Color.hpp>

QPalette Color::bg_primary() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(255, 255, 255));
  return pal;
}

QPalette Color::text_primary() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(255, 255, 255));
  return pal;
}

QPalette Color::text_secondary() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(175, 175, 175));
  return pal;
}

QPalette Color::text_selected() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(155, 89, 182));
  return pal;
}

QPalette Color::login_bg_primary() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(230, 147, 234));
  return pal;
}

QPalette Color::login_bg_failure() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(192, 57, 43));
  return pal;
}

QPalette Color::login_bg_success() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(46, 204, 113));
  return pal;
}

QPalette Color::grid_red() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(222, 43, 43));
  return pal;
}

QPalette Color::grid_blue() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(53, 177, 241));
  return pal;
}

QPalette Color::grid_green() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(0, 219, 65));
  return pal;
}

QPalette Color::grid_yellow() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(241, 158, 46));
  return pal;
}

QPalette Color::grid_purple() {
  QPalette pal;
  pal.setColor(QPalette::Background, QColor(208, 51, 237));
  return pal;
}

QPalette Color::assignment_green() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(46, 204, 113));
  return pal;
}

QPalette Color::assignment_yellow() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(241, 196, 15));
  return pal;
}

QPalette Color::assignment_red() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(231, 76, 60));
  return pal;
}

QPalette Color::text_assignment_open() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(157, 157, 157));
  return pal;
}

QPalette Color::text_assignment_closed() {
  QPalette pal;
  pal.setColor(QPalette::WindowText, QColor(128, 128, 128));
  return pal;
}
