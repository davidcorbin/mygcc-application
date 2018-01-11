/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <QColor>
#include <QPalette>

#ifndef INCLUDE_UI_COLOR_HPP_
#define INCLUDE_UI_COLOR_HPP_

class Color {
 public:
  // Global colors
  static QPalette bg_primary();
  static QPalette text_primary();
  static QPalette text_secondary();
  static QPalette text_selected();

  // Login colors
  static QPalette login_bg_primary();
  static QPalette login_bg_failure();
  static QPalette login_bg_success();

  // Grid item colors
  static QPalette grid_red();
  static QPalette grid_blue();
  static QPalette grid_green();
  static QPalette grid_yellow();
  static QPalette grid_purple();
};


#endif  // INCLUDE_UI_COLOR_HPP_
