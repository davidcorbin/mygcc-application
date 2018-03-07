/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/MainWindow.hpp>
#include <include/ui/ProfilePanel.hpp>
#include <include/ui/SidebarPanel.hpp>
#include <include/ui/FeedbackListItem.hpp>
#include <include/ui/Color.hpp>
#include <QLocale>
#include <QPainter>
#include <QCloseEvent>
#include <QCoreApplication>
#include <vector>
#include <string>

#define WINDOW_TITLE            "Facade [SNAPSHOT]"

#define MIN_HEIGHT        450
#define SIDEBAR_WIDTH     240
#define BODY_WIDTH        500
#define MIN_WIDTH         (SIDEBAR_WIDTH + BODY_WIDTH)

MainWindow::MainWindow(JavaIntegration *ji) : QMainWindow(nullptr),
                                              javaIntegration(ji) {
  setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
  setWindowTitle(WINDOW_TITLE);

  auto *profPanel = new ProfilePanel(new std::string("John Smith"),
                                     new std::string("Computer Science"),
                                     new std::string("GCCshield.jpg"));
  profPanel->setup();

  auto *biohw1 = new Assignment(new std::string("https://davcor.co"),
                                new std::string("https://google.com"),
                                new std::string("BIOL 101 Lab Grade"),
                                new std::string("Thursday, December 21"),
                                new std::string("Description"),
                                true,
                                new std::string("--"),
                                0,
                                0.0,
                                0);
  auto *biohw2 = new Assignment(new std::string("https://davcor.co"),
                                new std::string("https://google.com"),
                                new std::string("BIOL 101 Lab Grade"),
                                new std::string(""),
                                new std::string("Description"),
                                false,
                                new std::string("A+"),
                                2.25,
                                100.0,
                                3.0);
  auto *student1 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student2 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student3 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student4 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student5 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student6 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student7 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *student8 = new Student(nullptr,
                               false,
                               new std::string("David Corbin"),
                               123456);
  auto *bio = new Course(new std::string("Biology 1"),
                         new std::string("BIOL101"));
  bio->addAssignment(biohw1);
  bio->addAssignment(biohw2);
  bio->addStudent(student1);
  bio->addStudent(student2);
  bio->addStudent(student3);
  bio->addStudent(student4);
  bio->addStudent(student5);
  bio->addStudent(student6);
  bio->addStudent(student7);
  bio->addStudent(student8);
  auto *calc = new Course(new std::string("Calculus 3"),
                          new std::string("MATH261"));
  auto *dis = new Course(new std::string("Discrete Math"),
                         new std::string("MATH213"));
  auto *writ = new Course(new std::string("Writing"),
                          new std::string("WRIT101"));
  auto *prog = new Course(new std::string("Programming 2"),
                          new std::string("COMP220"));
  classes = {bio, calc, dis, writ, prog};

  for (Course *cour : classes) {
    auto *cv = new CourseView(cour, BODY_WIDTH);
    cv->setup();
    cv->setVisible(false);
    courseViews.push_back(cv);
  }

  auto *sidebarPanel = new SidebarPanel(&classes);
  sidebarPanel->setup();

  auto *feedbackListItem = new FeedbackListItem;
  feedbackListItem->setup();

  auto *sidebarLayout = new QGridLayout;
  sidebarLayout->addWidget(profPanel, 0, 0);
  sidebarLayout->addWidget(sidebarPanel, 1, 0);
  sidebarLayout->addWidget(feedbackListItem, 2, 0);
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

  auto *items = new std::vector<GridItem *>();
  items->push_back(new GridItem(new QString("13"),
                                new QString("chapels left"),
                                Color::grid_blue()));
  items->push_back(new GridItem(new QString("7"),
                                new QString("assignments"),
                                Color::grid_green()));
  items->push_back(new GridItem(new QString("15"),
                                new QString("chapels received"),
                                Color::grid_purple()));
  items->push_back(new GridItem(new QString("2/7"),
                                new QString("assignments received"),
                                Color::grid_red()));
  items->push_back(new GridItem(new QString("PDF"),
                                new QString("Programming Project 2 PDF"),
                                Color::grid_yellow()));

  // Setup the Home view
  infogrid = new InfoGrid(items);
  infogrid->setup();
  infogrid->show();

  // Setup class view
  feedbackPanel = new FeedbackPanel;
  feedbackPanel->setup();
  feedbackPanel->hide();

  // Body width constraints
  infogrid->setMinimumWidth(BODY_WIDTH);

  // Body height constraints
  infogrid->setMinimumHeight(MIN_HEIGHT);

  centralLayout = new QGridLayout;
  centralLayout->addWidget(sidebar, 0, 0);
  centralLayout->addWidget(infogrid, 0, 1);
  centralLayout->addWidget(feedbackPanel, 0, 1);
  // Add Course Views
  for (CourseView *cv : courseViews) {
    centralLayout->addWidget(cv, 0, 1);
  }
  currentBodyWidget = infogrid;
  centralLayout->setSpacing(3);
  centralLayout->setContentsMargins(0, 0, 0, 0);

  centralWidget = new QWidget;
  centralWidget->setLayout(centralLayout);
  centralWidget->setStyleSheet("background-color: rgb(46, 46, 50)");

  // Show login panel
  loginPanel = new LoginPanel(MIN_WIDTH, MIN_HEIGHT);
  loginPanel->setup();
  setCentralWidget(loginPanel);
}

void MainWindow::viewFeedbackPanel() {
  currentBodyWidget->hide();
  feedbackPanel->show();
  currentBodyWidget = feedbackPanel;
}

void MainWindow::viewGridPanel() {
  currentBodyWidget->hide();
  infogrid->show();
  currentBodyWidget = infogrid;
}

void MainWindow::viewCourse(Course *course) {
  currentBodyWidget->hide();
  for (CourseView *cv : courseViews) {
    if (cv->course == course) {
      cv->show();
      currentBodyWidget = cv;
    }
  }
}

// When window becomes visible, trigger event
void MainWindow::showEvent(QShowEvent *event) {
}

void MainWindow::closeEvent(QCloseEvent *event) {
  javaIntegration->stopAPIServerCmd();
}
