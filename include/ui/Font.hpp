/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_FONT_HPP_
#define INCLUDE_UI_FONT_HPP_

#include <QFont>

#include <string>

class Font {
 public:
  // Profile panel
  static QFont profileName();
  static QFont profileMajor();

  // Sidebar
  static QFont sidebarItem();

  // Startup panel
  static QFont startupTitle();
  static QFont startupSubtitle();
  static QFont startupInput();

  // Grid panel
  static QFont heroNumber();
  static QFont subtitleLabel();

  // Feedback panel
  static QFont feedbackTextbox();
 private:
  static QString loadFont(std::string font);
};


#endif  // INCLUDE_UI_FONT_HPP_
