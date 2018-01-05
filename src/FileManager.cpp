/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/FileManager.hpp>

#include <sys/types.h>
#include <sys/stat.h>

#if (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64))
#include <include/dirent.h>
#else
#include <dirent.h>
#endif

#include <include/OS.hpp>
#include <include/FileNotFound.hpp>
#include <QCoreApplication>
#include <QDir>
#include <string>

#define MACOS_DATA_DIR      "/Library/Application Support/Facade"
#define WIN_DATA_DIR        "\\AppData\\Roaming\\Facade"
#define LINUX_DATA_DIR      "./facade"

std::string FileManager::getDataDir() {
  std::string osname = OS::getOSName();

  if (osname == "macOSX") {
    auto *homedir = getenv("HOME");
    std::string home(homedir);
    return home + MACOS_DATA_DIR;
  } else if (osname == "Unix" || osname == "Linux") {
    auto *homedir = getenv("HOME");
    std::string home(homedir);
    return home + LINUX_DATA_DIR;
  } else if (osname == "Windows 32-bit" || osname == "Windows 64-bit") {
    auto *homedir = getenv("APPDATA");
    std::string home(homedir);
    return home + WIN_DATA_DIR;
  } else {
    return getenv("HOME");
  }
}

bool FileManager::dirExists(std::string directory) {
  DIR* dir = opendir(directory.c_str());
  if (dir) {
    closedir(dir);
    return true;
  }
  return false;
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
    std::string full = abs + "/Resources/" + file;
    // Check if file exists
    if (!file.empty() && !fileExists(full)) {
      qFatal("Resource not found: %s\n", full.c_str());
    }
    return full;
  } else if (osname == "Linux" || osname == "Unix") {
    std::string abs = QCoreApplication::applicationDirPath().toStdString();
    std::string full = abs + "/Resources/" + file;
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
  QDir dir(path.c_str());
  if (!dir.exists()){
    dir.mkdir(".");
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
