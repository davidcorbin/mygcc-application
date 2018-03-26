/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/MainWindow.hpp>
#include <include/Logging.hpp>
#include <QApplication>
#include <QtGlobal>

/**
 * Starts the server and application.
 * @param argc number of arguments
 * @param argv arguments
 * @return status of the application
 */
int main(int argc, char *argv[]) {
  //  Scale GUI properly on Windows
  #if QT_VERSION > QT_VERSION_CHECK(5, 6, 0)
  qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
  #endif

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("facade");
  QCoreApplication::setApplicationName("Facade");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  // Start logging
  qInstallMessageHandler(Logging::customLogger);

  //  High DPI support
  #if QT_VERSION > QT_VERSION_CHECK(5, 6, 0)
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  #endif

  auto *ji = new JavaIntegration;
  ji->startAPIThread();

  auto *login = new Login();
  login->testAPIConnection();

  auto *schedule = new Schedule(login);
  auto *user = new User(login);

  MainWindow w(ji, login, schedule, user);
  w.show();

  return app.exec();
}
