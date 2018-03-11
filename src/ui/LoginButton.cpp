/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/LoginButton.hpp>
#include <include/ui/Font.hpp>
#include <include/ui/LoginPanel.hpp>

LoginButton::LoginButton(const QString *text) {
  setText(*text);
}

void LoginButton::setup() {
  setStyleSheet("background: rgb(182, 45, 214);"
                    "border-radius: 18px;"
                    "padding: 10px 30px;"
                    "color: #fff;");
  setGraphicsEffect(LoginPanel::shadowEffect(this, 15, "#888"));
  setFont(Font::startupInput());
  setFocusPolicy(Qt::NoFocus);
}

QColor LoginButton::color() {
  auto *col = new QColor(0, 0, 0);
  return *col;
}

// Sets background gradient from background color by subtracting from RGB value.
// Will throw error when RGB values are out of range.
void LoginButton::setBackgroundColor(QColor color) {
  setStyleSheet(QString("background: rgb(%1, %2, %3);"
                            "border-radius: 18px;"
                            "padding: 10px 30px;"
                            "color: #fff;")
                    .arg(color.red())
                    .arg(color.green())
                    .arg(color.blue()));
}
