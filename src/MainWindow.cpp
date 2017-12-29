/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/MainWindow.hpp>

#include <include/Color.hpp>
#include <include/Font.hpp>
#include <include/ProfilePanel.hpp>

#include <QLocale>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QBitmap>
#include <QPainter>
#include <QCoreApplication>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
  setWindowTitle("Facade");

  auto *pp = new ProfilePanel(new std::string("John Smith"),
                             new std::string("Computer Science"),
                             new std::string("custom_user_image.jpg"));
  pp->setup();

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
  sidebarLayout->addWidget(pp, 0, 0);
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
