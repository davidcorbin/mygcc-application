/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/Font.hpp>
#include <include/FileManager.hpp>
#include <QFontDatabase>
#include <QStringList>
#include <string>

#define LATO_LIGHT            "Lato-Light.ttf"
#define MONTSERRAT_REGULAR    "Montserrat-Regular.ttf"


QFont Font::profileName() {
  auto *font = new QFont();
  font->setPointSize(20);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::profileMajor() {
  auto *font = new QFont();
  font->setPointSize(11);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::sidebarItem() {
  auto *font = new QFont();
  font->setPointSize(14);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::startupTitle() {
  auto *font = new QFont();
  font->setPointSize(36);
  font->setFamily(loadFont(MONTSERRAT_REGULAR));
  return *font;
}

QFont Font::startupSubtitle() {
  auto *font = new QFont();
  font->setPointSize(14);
  font->setFamily(loadFont(MONTSERRAT_REGULAR));
  return *font;
}

QFont Font::startupInput() {
  auto *font = new QFont();
  font->setPointSize(14);
  font->setFamily(loadFont(MONTSERRAT_REGULAR));
  return *font;
}

QFont Font::heroNumber() {
  auto *font = new QFont();
  font->setPointSize(50);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::subtitleLabel() {
  auto *font = new QFont();
  font->setPointSize(10);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::feedbackTextbox() {
  auto *font = new QFont();
  font->setPointSize(12);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::assignmentGrade() {
  auto *font = new QFont();
  font->setPointSize(32);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::assignmentPoints() {
  auto *font = new QFont();
  font->setPointSize(18);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::assignmentName() {
  auto *font = new QFont();
  font->setPointSize(18);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QFont Font::assignmentDueDate() {
  auto *font = new QFont();
  font->setPointSize(18);
  font->setFamily(loadFont(LATO_LIGHT));
  return *font;
}

QString Font::loadFont(std::string font) {
  auto *fm = new FileManager();
  std::string absPath = fm->getResourcePath(font);
  int id = QFontDatabase::addApplicationFont(absPath.c_str());
  return QFontDatabase::applicationFontFamilies(id).at(0);
}
