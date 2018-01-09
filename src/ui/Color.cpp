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
