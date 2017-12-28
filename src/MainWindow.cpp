/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/MainWindow.hpp>

#include <include/Color.hpp>
#include <include/ProfileImage.hpp>

#include <QLocale>
#include <QPushButton>
#include <QStackedLayout>
#include <QGraphicsDropShadowEffect>
#include <QBitmap>
#include <QPainter>
#include <QLabel>
#include <QCoreApplication>
#include <include/Font.hpp>

#define PROFILE_IMG_DIM   40

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
  setWindowTitle("Facade");

  // Profile box
  auto *profileImage = new ProfileImage("GCCshield.jpg");
  QPixmap scal = profileImage->setUp();

  auto *profImg = new QLabel;
  profImg->setPixmap(scal.scaled(PROFILE_IMG_DIM,
                                 PROFILE_IMG_DIM,
                                 Qt::KeepAspectRatio,
                                 Qt::SmoothTransformation));
  profImg->setStyleSheet("border-bottom: none;");
  profImg->setMaximumWidth(60);
  profImg->setContentsMargins(10, 0, 10, 0);

  auto *nameLabel = new QLabel("John Smith");
  nameLabel->setPalette(Color::text_primary());
  nameLabel->setStyleSheet("border-bottom: none;");
  nameLabel->setFont(Font::profileName());

  auto *majorLabel = new QLabel("Computer Science");
  majorLabel->setPalette(Color::text_primary());
  majorLabel->setStyleSheet("border-bottom: none;");
  majorLabel->setFont(Font::profileMajor());

  auto *profTextLayout = new QVBoxLayout;
  profTextLayout->addWidget(nameLabel);
  profTextLayout->addWidget(majorLabel);
  profTextLayout->setContentsMargins(0, 0, 0, 0);
  profTextLayout->setSpacing(0);

  auto *profTextWidget = new QWidget;
  profTextWidget->setLayout(profTextLayout);
  profTextWidget->setStyleSheet("border-bottom: none;");

  auto *profileLayout = new QGridLayout;
  profileLayout->addWidget(profImg, 0, 0);
  profileLayout->addWidget(profTextWidget, 0, 1);

  auto *profileCont = new QWidget;
  profileCont->setLayout(profileLayout);
  profileCont->setMaximumHeight(65);
  profileCont->setMinimumHeight(65);
  profileCont->setStyleSheet("border-bottom:1px solid rgb(40, 40, 45);");

  // Sidebar
  auto *class1 = new QLabel("Home");
  class1->setContentsMargins(20, 3, 5, 3);
  class1->setPalette(Color::text_secondary());
  class1->setFont(Font::sidebarItem());

  auto *sidebarItemLayout = new QVBoxLayout;
  sidebarItemLayout->addWidget(class1);
  sidebarItemLayout->addStretch();

  auto *tabCont = new QWidget;
  tabCont->setPalette(Color::bg_primary());
  tabCont->setLayout(sidebarItemLayout);

  auto *sidebarLayout = new QGridLayout;
  sidebarLayout->addWidget(profileCont, 0, 0);
  sidebarLayout->addWidget(tabCont, 1, 0);
  sidebarLayout->setContentsMargins(0, 0, 0, 0);
  sidebarLayout->setSpacing(0);

  auto *shadow = new QGraphicsDropShadowEffect;
  shadow->setBlurRadius(6);
  shadow->setXOffset(4);
  shadow->setYOffset(0);
  shadow->setColor(QColor(48, 46, 50));

  auto *sidebar = new QWidget;
  // Sidebar width constraints
  sidebar->setMaximumWidth(240);
  sidebar->setMinimumWidth(240);
  sidebar->setLayout(sidebarLayout);
  sidebar->setGraphicsEffect(shadow);

  // Sidebar height constraints
  sidebar->setMinimumHeight(450);

  auto *mainBody = new QWidget;

  // Body width constraints
  mainBody->setMinimumWidth(500);

  // Body height constraints
  mainBody->setMinimumHeight(450);

  auto *centralLayout = new QGridLayout;
  centralLayout->addWidget(sidebar, 0, 0);
  centralLayout->addWidget(mainBody, 0, 1);
  centralLayout->setSpacing(3);
  centralLayout->setContentsMargins(0, 0, 0, 0);

  auto *centralWidget = new QWidget;
  centralWidget->setLayout(centralLayout);
  centralWidget->setStyleSheet("background-color: rgb(46, 46, 50)");

  setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
}
