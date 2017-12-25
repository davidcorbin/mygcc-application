/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include "include/Color.hpp"

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
