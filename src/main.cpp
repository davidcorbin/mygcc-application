/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/MainWindow.hpp>
#include <include/api/JavaIntegration.hpp>
#include <QApplication>
#include <QtGlobal>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("facade");
  QCoreApplication::setApplicationName("Facade");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  //  High DPI support
  #if QT_VERSION > QT_VERSION_CHECK(5, 6, 0)
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  #endif

  JavaIntegration *ji = new JavaIntegration;
  ji->startAPIThread();

  MainWindow w;
  w.show();

  return app.exec();
}
