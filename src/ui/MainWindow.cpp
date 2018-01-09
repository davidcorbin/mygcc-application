/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/MainWindow.hpp>
#include <include/ui/ProfilePanel.hpp>
#include <include/ui/SidebarPanel.hpp>
#include <include/ui/LoginPanel.hpp>
#include <QLocale>
#include <QPainter>
#include <QCoreApplication>
#include <vector>
#include <string>

#define MIN_HEIGHT        450
#define SIDEBAR_WIDTH     240
#define BODY_WIDTH        500
#define MIN_WIDTH         SIDEBAR_WIDTH + BODY_WIDTH

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
  setWindowTitle("Facade");

  auto *profPanel = new ProfilePanel(new std::string("John Smith"),
                                     new std::string("Computer Science"),
                                     new std::string("GCCshield.jpg"));
  profPanel->setup();

  auto *bio = new Course("Biology 1", "BIOL101");
  auto *calc = new Course("Calculus 3", "MATH261");
  auto *dis = new Course("Discrete Math", "MATH213");
  auto *writ = new Course("Writing", "WRIT101");
  auto *prog = new Course("Programming 2", "COMP220");
  std::vector<Course *> classes = {bio, calc, dis, writ, prog};

  auto *sidebarPanel = new SidebarPanel(&classes);
  sidebarPanel->setup();

  auto *sidebarLayout = new QGridLayout;
  sidebarLayout->addWidget(profPanel, 0, 0);
  sidebarLayout->addWidget(sidebarPanel, 1, 0);
  sidebarLayout->setContentsMargins(0, 0, 0, 0);
  sidebarLayout->setSpacing(0);

  auto *shadow = new QGraphicsDropShadowEffect;
  shadow->setBlurRadius(6);
  shadow->setXOffset(4);
  shadow->setYOffset(0);
  shadow->setColor(QColor(48, 46, 50));

  auto *sidebar = new QWidget;
  // Sidebar width constraints
  sidebar->setMaximumWidth(SIDEBAR_WIDTH);
  sidebar->setMinimumWidth(SIDEBAR_WIDTH);
  sidebar->setLayout(sidebarLayout);
  sidebar->setGraphicsEffect(shadow);

  // Sidebar height constraints
  sidebar->setMinimumHeight(450);

  qhblayout = new QHBoxLayout;
  testlabel = new QLabel();
  testlabel->setText("Home");
  testlabel->setAlignment(Qt::AlignCenter);
  testlabel->setStyleSheet("color: white");
  qhblayout->addWidget(testlabel);
  mainBody = new QWidget;
  mainBody->setLayout(qhblayout);

  // Body width constraints
  mainBody->setMinimumWidth(BODY_WIDTH);

  // Body height constraints
  mainBody->setMinimumHeight(MIN_HEIGHT);

  centralLayout = new QGridLayout;
  centralLayout->addWidget(sidebar, 0, 0);
  centralLayout->addWidget(mainBody, 0, 1);
  centralLayout->setSpacing(3);
  centralLayout->setContentsMargins(0, 0, 0, 0);

  centralWidget = new QWidget;
  centralWidget->setLayout(centralLayout);
  centralWidget->setStyleSheet("background-color: rgb(46, 46, 50)");

  // setCentralWidget(centralWidget);
  
  auto *labelPanel = new LoginPanel(MIN_WIDTH, MIN_HEIGHT);
  labelPanel->setup();
  setCentralWidget(labelPanel);
}

void MainWindow::setTestText(std::string text) {
  testlabel->setText(text.c_str());
}
