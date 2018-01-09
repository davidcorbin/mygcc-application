/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_LOGINBUTTON_HPP_
#define INCLUDE_UI_LOGINBUTTON_HPP_

#include <QPushButton>

class LoginButton : public QPushButton {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setBackgroundColor)

 public:
  explicit LoginButton(const QString *text);
  void setup();

 private:
  QColor color();
  void setBackgroundColor(QColor color);
};


#endif  // INCLUDE_UI_LOGINBUTTON_HPP_
