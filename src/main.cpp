/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <QApplication>

#include <include/ui/MainWindow.hpp>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("facade");
    QCoreApplication::setApplicationName("Facade");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);  // DPI support

    MainWindow w;
    w.show();

    return app.exec();
}
