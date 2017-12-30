/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_FONT_HPP
#define FACADE_APPLICATION_FONT_HPP

#include <QFont>

class Font {
public:
  static QFont profileName();
  static QFont profileMajor();
  static QFont sidebarItem();

private:
  static QString loadFont(std::string font);
};


#endif //FACADE_APPLICATION_FONT_HPP
