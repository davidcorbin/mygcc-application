/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <QColor>
#include <QPalette>

#ifndef FACADE_APPLICATION_COLOR_HPP
#define FACADE_APPLICATION_COLOR_HPP

class Color {
public:
  static QPalette bg_primary();
  static QPalette text_primary();
  static QPalette text_secondary();
};


#endif //FACADE_APPLICATION_COLOR_HPP
