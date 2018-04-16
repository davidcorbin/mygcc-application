/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/LoginPanel.hpp>
#include <include/ui/Font.hpp>
#include <include/ui/Color.hpp>
#include <QStyleOption>
#include <QPainter>

#define TITLE_STR   "Facade"
#define SUBTIT_STR  "A desktop client for myGCC"

LoginPanel::LoginPanel(int min_width, int min_height, Login *loginObj) :
    min_width(min_width), min_height(min_height), loginObj(loginObj),
    bgPrimary(Color::login_bg_primary().color(QPalette::Background)),
    bgSuccess(Color::login_bg_success().color(QPalette::Background)),
    bgFailure(Color::login_bg_failure().color(QPalette::Background)) {
  startupLayout = new QVBoxLayout;
  usernameText = new QLineEdit;
  passwordText = new QLineEdit;
  subtitleLabel = new QLabel(SUBTIT_STR);
  titleLabel = new QLabel(TITLE_STR);
  loginButton = new LoginButton(new QString("Login"));
  setBackgroundColor(bgPrimary);
  bgState = PRIMARY;
  isloggingIn = false;

  // Activate animations when Login signals success or failure
  connect(loginObj, SIGNAL(authSuccessful()), this, SLOT(authSuccessful()));
  connect(loginObj, SIGNAL(authInvalidCred()), this, SLOT(authFailure()));
}

void LoginPanel::setup() {
  setupTitleLabel();
  setupSubtitleLabel();
  setupUsernameTextInput();
  setupPasswordTextInput();
  loginButton->setup();

  // Submit when login button pressed
  connect(loginButton, SIGNAL(released()), this, SLOT(login()));

  // Submit when return clicked in password input
  connect(passwordText, SIGNAL(returnPressed()), this, SLOT(login()));

  startupLayout->addWidget(titleLabel);
  startupLayout->setAlignment(titleLabel, Qt::AlignCenter);
  startupLayout->addWidget(subtitleLabel);
  startupLayout->setAlignment(subtitleLabel, Qt::AlignCenter);
  startupLayout->addWidget(usernameText);
  startupLayout->setAlignment(usernameText, Qt::AlignCenter);
  startupLayout->addWidget(passwordText);
  startupLayout->setAlignment(passwordText, Qt::AlignCenter);
  startupLayout->addWidget(loginButton);
  startupLayout->setAlignment(loginButton, Qt::AlignCenter);
  startupLayout->setAlignment(Qt::AlignCenter);

  setMinimumWidth(min_width);
  setMinimumHeight(min_height);
  setLayout(startupLayout);
}

void LoginPanel::setupTitleLabel() {
  titleLabel->setAlignment(Qt::AlignCenter);
  titleLabel->setStyleSheet("background: none");
  titleLabel->setFont(Font::startupTitle());
  titleLabel->setPalette(Color::text_primary());
  titleLabel->setGraphicsEffect(shadowEffect(titleLabel, 15));
  titleLabel->setContentsMargins(0, 0, 0, 0);
}

void LoginPanel::setupSubtitleLabel() {
  subtitleLabel->setAlignment(Qt::AlignCenter);
  subtitleLabel->setStyleSheet("background: none");
  subtitleLabel->setFont(Font::startupSubtitle());
  subtitleLabel->setPalette(Color::text_primary());
  subtitleLabel->setGraphicsEffect(shadowEffect(subtitleLabel, 15));
  subtitleLabel->setContentsMargins(0, 0, 0, 30);
}

void LoginPanel::setupUsernameTextInput() {
  usernameText->setFixedWidth(220);
  usernameText->setStyleSheet("background: #fff; "
                                  "border-radius: 3px; "
                                  "padding: 10px; "
                                  "color: #000;");
  usernameText->setFont(Font::startupInput());
  usernameText->setPlaceholderText("Student ID #");
  usernameText->setGraphicsEffect(shadowEffect(usernameText, 20, "#777"));
  usernameText->setContentsMargins(0, 0, 0, 5);
  usernameText->setAttribute(Qt::WA_MacShowFocusRect, false);  // macOS
}

void LoginPanel::setupPasswordTextInput() {
  passwordText->setFixedWidth(220);
  passwordText->setStyleSheet("background: #fff; "
                                  "border-radius: 3px; "
                                  "padding: 10px; "
                                  "color: #000;");
  passwordText->setFont(Font::startupInput());
  passwordText->setPlaceholderText("Password");
  passwordText->setGraphicsEffect(shadowEffect(passwordText, 20, "#777"));
  passwordText->setEchoMode(QLineEdit::Password);
  passwordText->setContentsMargins(0, 0, 0, 25);
  passwordText->setAttribute(Qt::WA_MacShowFocusRect, false);  // macOS
}

bool LoginPanel::login() {
  if (isloggingIn) {
    return false;
  }
  auto username = usernameText->text().toStdString();
  auto password = passwordText->text().toStdString();
  loginObj->login(&username, &password, true);
  loginButton->setText("Logging in...");
  isloggingIn = true;
  return false;
}

void LoginPanel::authSuccessful() {
  auto *backgroundAnimation = successAnimation(this);
  auto *buttonAnimation = successAnimation(loginButton);
  backgroundAnimation->start();
  buttonAnimation->start();
  bgState = SUCCESS;
  usernameText->hide();
  passwordText->hide();
  loginButton->setText("Login");
  loginButton->hide();
  subtitleLabel->setText("Loading...");
  isloggingIn = false;
}

void LoginPanel::authFailure() {
  loginButton->setText("Login");
  auto *backgroundAnimation = errorAnimation(this);
  auto *buttonAnimation = errorAnimation(loginButton);
  backgroundAnimation->start();
  buttonAnimation->start();
  bgState = FAILURE;
  isloggingIn = false;
}

QGraphicsDropShadowEffect* LoginPanel::shadowEffect(QObject *parent,
                                                    int blurRadius,
                                                    const char *color) {
  auto *effect = new QGraphicsDropShadowEffect(parent);
  effect->setBlurRadius(blurRadius);
  effect->setColor(QColor(color));
  effect->setOffset(1, 1);
  return effect;
}

void LoginPanel::paintEvent(QPaintEvent *) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QColor LoginPanel::color() {
  return bgPrimary;
}

// Sets background gradient from background color by subtracting from RGB value.
// Will throw error when RGB values are out of range.
void LoginPanel::setBackgroundColor(QColor color) {
  setStyleSheet(QString("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                            "stop:0 rgb(%1, %2, %3), stop:1 rgb(%4, %5, %6));")
                    .arg(color.red())
                    .arg(color.green())
                    .arg(color.blue())
                    .arg(color.red()-40)
                    .arg(color.green()-40)
                    .arg(color.blue()-40));
}

QPropertyAnimation* LoginPanel::errorAnimation(QObject *element) {
  auto *animation = new QPropertyAnimation(element, "color");
  animation->setEasingCurve(QEasingCurve::InSine);
  animation->setDuration(750);
  if (bgState == PRIMARY) {
    animation->setStartValue(bgPrimary);
  } else if (bgState == SUCCESS) {
    animation->setStartValue(bgSuccess);
  } else if (bgState == FAILURE) {
    animation->setStartValue(bgFailure);
  }
  animation->setEndValue(bgFailure);
  return animation;
}

QPropertyAnimation* LoginPanel::successAnimation(QObject *element) {
  auto *animation = new QPropertyAnimation(element, "color");
  animation->setEasingCurve(QEasingCurve::InSine);
  animation->setDuration(750);
  if (bgState == PRIMARY) {
    animation->setStartValue(bgPrimary);
  } else if (bgState == FAILURE) {
    animation->setStartValue(bgFailure);
  } else if (bgState == SUCCESS) {
    animation->setStartValue(bgSuccess);
  }
  animation->setEndValue(bgSuccess);
  return animation;
}
