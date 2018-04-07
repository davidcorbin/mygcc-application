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
#include <QtWidgets>
#include <vector>
#include <string>

#define WINDOW_TITLE            "Facade v0.4.1"

#define MIN_HEIGHT        450
#define SIDEBAR_WIDTH     240
#define BODY_WIDTH        500
#define MIN_WIDTH         (SIDEBAR_WIDTH + BODY_WIDTH)

MainWindow::MainWindow(JavaIntegration *ji,
                       Login *login,
                       Schedule *schedule,
                       User *user) : QMainWindow(nullptr),
                                     javaIntegration(ji),
                                     login(login),
                                     schedule(schedule),
                                     user(user) {
  setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
  setWindowTitle(WINDOW_TITLE);

  connect(schedule, SIGNAL(coursesLoaded()),
          this, SLOT(startupCallbackHandler()));
  connect(schedule, SIGNAL(internalServerError()), this, SLOT(logout()));
  connect(user, SIGNAL(userLoaded()),
          this, SLOT(startupCallbackHandler()));

  centralWidget = new QWidget;
  centralWidget->setStyleSheet("background-color: rgb(46, 46, 50)");

  // Show login panel
  loginPanel = new LoginPanel(MIN_WIDTH, MIN_HEIGHT, login);
  loginPanel->setup();
  setCentralWidget(loginPanel);

  chapel = new Chapel(login);

  infogrid = new InfoGrid();
  infogrid->setup();

  connect(chapel, SIGNAL(chapelsReceived()), this, SLOT(addChapelGridItems()));

  auto *logoutAction = new QAction(tr("&Log Out"), this);
  connect(logoutAction, SIGNAL(triggered()), this, SLOT(logoutRestart()));

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(logoutAction);
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

void MainWindow::showHomeWidget() {
  auto classes = *schedule->getCourses();

  for (Course *cour : classes) {
    auto *cv = new CourseView(cour, BODY_WIDTH);
    cv->setup();
    cv->setVisible(false);
    courseViews.push_back(cv);
  }

  auto *profPanel = new ProfilePanel(user);
  profPanel->setup();

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
  shadow->setBlurRadius(1);
  shadow->setXOffset(1);
  shadow->setYOffset(0);
  shadow->setColor(QColor(40, 40, 45));

  auto *sidebar = new QWidget;
  // Sidebar width constraints
  sidebar->setMaximumWidth(SIDEBAR_WIDTH);
  sidebar->setMinimumWidth(SIDEBAR_WIDTH);
  sidebar->setLayout(sidebarLayout);
  sidebar->setGraphicsEffect(shadow);

  // Sidebar height constraints
  sidebar->setMinimumHeight(450);

  // Setup the Home view
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

  centralWidget->setLayout(centralLayout);

  loginPanel->hide();
  setCentralWidget(centralWidget);
}

// When window becomes visible, trigger event
void MainWindow::showEvent(QShowEvent *event) {
}

void MainWindow::closeEvent(QCloseEvent *event) {
  javaIntegration->stopAPIServerCmd();
}

//
// Ensure that all UI elements are loaded before showing home screen.
//
void MainWindow::startupCallbackHandler() {
  if (user->isUserRetrieved() && schedule->isScheduleRetrieved()) {
    showHomeWidget();
  }
}

void MainWindow::logout() {
  loginPanel->show();
  loginPanel->authFailure();
}

void MainWindow::logoutRestart() {
  // Delete user data file
  login->deleteUserData();

  // Quit application and restart
  qApp->quit();
  QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::addChapelGridItems() {
  int remaining = chapel->getRemaining();
  int required = chapel->getRequired();
  int attended = chapel->getAttended();
  int makeups = chapel->getMakeups();

  // Chapels remaining
  QString header = QString("%1/%2").arg(QString::number(remaining),
                                        QString::number(required + makeups));
  infogrid->addGridItem(new GridItem(&header,
                                     new QString("Chapels remaining"),
                                     Color::grid_blue()));

  // Percent of chapels completed
  auto pc = static_cast<int>(((attended/
      static_cast<float>(required + makeups))) * 100 + 0.5);
  QString percentHeader = QString("%1%").arg(QString::number(pc));
  infogrid->addGridItem(new GridItem(&percentHeader,
                                     new QString("Chapels completed"),
                                     Color::grid_blue()));

  // Chapels attended
  QString attendedHeader = QString("%1").arg(QString::number(attended));
  infogrid->addGridItem(new GridItem(&attendedHeader,
                                     new QString("Chapels attended"),
                                     Color::grid_blue()));
}
