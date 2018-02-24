/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/FileManager.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <include/OS.hpp>
#include <include/FileNotFound.hpp>
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <string>

std::string FileManager::getDataDir() {
  #if QT_VERSION > QT_VERSION_CHECK(5, 4, 0)
    std::string datadir = QStandardPaths::writableLocation(
      QStandardPaths::AppDataLocation).toStdString();
  #else
    std::string datadir = QStandardPaths::writableLocation(
      QStandardPaths::DataLocation).toStdString();
  #endif

  if (datadir.empty()) {
    qFatal("No app data location found for OS");
  }
  return datadir;
}

std::string FileManager::getResourcePath(std::string file = "") {
  std::string osname = OS::getOSName();

  if (osname == "macOSX") {
    std::string abs = QCoreApplication::applicationDirPath().toStdString();
    std::string full = abs + "/../Resources/" + file;
    // Check if file exists
    if (!file.empty() && !fileExists(full)) {
      qFatal("Resource not found: %s\n", full.c_str());
    }
    return full;
  } else if (osname == "Windows 32-bit" || osname == "Windows 64-bit") {
    std::string abs = QCoreApplication::applicationDirPath().toStdString();
    std::string full = abs + "/" + file;
    // Check if file exists
    if (!file.empty() && !fileExists(full)) {
      qFatal("Resource not found: %s\n", full.c_str());
    }
    return full;
  } else if (osname == "Linux" || osname == "Unix") {
    std::string abs = QCoreApplication::applicationDirPath().toStdString();
    std::string full = abs + "/res/" + file;
    // Check if file exists
    if (!file.empty() && !fileExists(full)) {
      qFatal("Resource not found: %s\n", full.c_str());
    }
    return full;
  } else {
    return "";
  }
}

std::string FileManager::getDataPath(std::string file = "") {
  auto path = getDataDir();

  // Make directory if not found
  auto qpath = QString::fromStdString(path);
  QDir dir(qpath);
  if (!dir.exists()) {
    dir.mkpath(qpath);

    // Set path permissions
    QFile::setPermissions(qpath, QFileDevice::ReadUser |
        QFileDevice::WriteUser | QFileDevice::ExeUser);
  }

  auto full = dir.absolutePath().toStdString() + "/" + file;

  // Check if file exists
  if (!file.empty() && !fileExists(full)) {
    throw FileNotFound(&full);
  }
  return full;
}

inline bool FileManager::fileExists(const std::string& name) {
  if (FILE *file = fopen(name.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}
