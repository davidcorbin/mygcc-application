/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/MainWindow.hpp>
#include <include/ui/ProfilePanel.hpp>
#include <include/ui/SidebarPanel.hpp>

#include <QLocale>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QBitmap>
#include <QPainter>
#include <QCoreApplication>

#include <vector>
#include <string>

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
