/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <QColor>
#include <QPalette>

#ifndef INCLUDE_UI_COLOR_HPP_
#define INCLUDE_UI_COLOR_HPP_

class Color {
 public:
  static QPalette bg_primary();
  static QPalette text_primary();
  static QPalette text_secondary();
  static QPalette text_selected();
  static QPalette login_bg_primary();
  static QPalette login_bg_failure();
  static QPalette login_bg_success();
};


#endif  // INCLUDE_UI_COLOR_HPP_
