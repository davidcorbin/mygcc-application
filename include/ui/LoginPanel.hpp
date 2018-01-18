/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_LOGINPANEL_HPP_
#define INCLUDE_UI_LOGINPANEL_HPP_

#include <include/ui/LoginButton.hpp>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QPropertyAnimation>

class LoginPanel : public QWidget {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setBackgroundColor)

 public:
  LoginPanel(int min_width, int min_height);
  void setup();
  LoginButton *loginButton;

  static QGraphicsDropShadowEffect* shadowEffect(QObject *parent,
                                                 int blurRadius,
                                                 const char *color = "#444");

 private:
  QLabel *titleLabel;
  QLabel *subtitleLabel;
  QLineEdit *usernameText;
  QLineEdit *passwordText;
  QVBoxLayout *startupLayout;
  const int min_width, min_height;
  const QColor bgPrimary, bgSuccess, bgFailure;
  enum BGSTATE {PRIMARY, SUCCESS, FAILURE};
  BGSTATE bgState;

  bool login();
  void paintEvent(QPaintEvent *) override;
  void setBackgroundColor(QColor color);
  QColor color();
  QPropertyAnimation* errorAnimation(QObject *element);
  QPropertyAnimation* successAnimation(QObject *element);
  void setupTitleLabel();
  void setupSubtitleLabel();
  void setupUsernameTextInput();
  void setupPasswordTextInput();

 private slots:  // NOLINT(whitespace/indent)
  void loginProcedure();
};

#endif  // INCLUDE_UI_LOGINPANEL_HPP_
