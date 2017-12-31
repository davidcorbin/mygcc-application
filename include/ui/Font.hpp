/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_FONT_HPP_
#define INCLUDE_UI_FONT_HPP_

#include <QFont>

#include <string>

class Font {
 public:
  static QFont profileName();
  static QFont profileMajor();
  static QFont sidebarItem();

 private:
  static QString loadFont(std::string font);
};


#endif  // INCLUDE_UI_FONT_HPP_
