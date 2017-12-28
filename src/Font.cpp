/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/Font.hpp>
#include <QFontDatabase>
#include <QStringList>
#include <include/FileManager.hpp>

#include <string>
#include <iostream>

QFont Font::profileName() {
  auto *font = new QFont();
  font->setPointSize(20);
  font->setFamily(loadFont("Lato-Light.ttf"));
  return *font;
}

QFont Font::profileMajor() {
  auto *font = new QFont();
  font->setPointSize(11);
  font->setFamily(loadFont("Lato-Light.ttf"));
  return *font;
}

QFont Font::sidebarItem() {
  auto *font = new QFont();
  font->setPointSize(14);
  font->setFamily(loadFont("Lato-Light.ttf"));
  return *font;
}

QString Font::loadFont(std::string font) {
  auto *fm = new FileManager();
  std::string absPath = fm->getResourcePath(font);
  int id = QFontDatabase::addApplicationFont(absPath.c_str());
  return QFontDatabase::applicationFontFamilies(id).at(0);
}
