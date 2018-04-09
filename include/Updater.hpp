/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UPDATER_HPP_
#define INCLUDE_UPDATER_HPP_

#include <QNetworkAccessManager>
#include <string>

class Updater : public QObject {
  Q_OBJECT

 public:
  Updater();
  void checkForUpdates();
  void installUpdates();

 private:
  bool maintenanceToolExists();
  std::string* installedVersion();
  void remoteVersion();

  std::string osname;
  std::string* installedApplicationVersion;
  std::string* remoteApplicationVersion;
  QNetworkAccessManager *nam;
};

#endif  // INCLUDE_UPDATER_HPP_
