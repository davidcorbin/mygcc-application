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

#define PROFILE_IMG_DIM   40

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
  setWindowTitle("Facade");

  auto *profileImage = new ProfileImage("GCCshield.jpg");
  QPixmap scal = profileImage->setUp();

  auto *profImg = new QLabel;
  profImg->setPixmap(scal.scaled(PROFILE_IMG_DIM,
                                 PROFILE_IMG_DIM,
                                 Qt::KeepAspectRatio,
                                 Qt::SmoothTransformation));

  auto *nameLabel = new QLabel("John Smith");
  nameLabel->setPalette(Color::text_primary());

  auto *profileLayout = new QGridLayout;
  profileLayout->addWidget(profImg, 0, 0);
  profileLayout->addWidget(nameLabel, 0, 1);

  auto *profileCont = new QWidget;
  profileCont->setLayout(profileLayout);
  profileCont->setMaximumHeight(75);
  profileCont->setMinimumHeight(75);

  auto *tabCont = new QWidget;
  tabCont->setPalette(Color::bg_primary());

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
