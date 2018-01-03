/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/FileManager.hpp>

#include <sys/stat.h>
#include <dirent.h>

#include <include/OS.hpp>
#include <include/FileNotFound.hpp>
#include <QCoreApplication>

#include <string>
#include <iostream>

#define MACOS_DATA_DIR      "/Library/Application Support/Facade"
#define WIN_DATA_DIR        "\\AppData\\Roaming\\Facade"
#define LINUX_DATA_DIR      "./facade"

// MinGW mkdir only has one parameter (the directory path)
#if (defined(_WIN32) || defined(__WIN32__) || defined(_WIN64))
#define mkdir(A, B) mkdir(A)
#endif

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
  auto dir = getDataDir();

  // Make directory if not found
  if (!dirExists(dir)) {
    mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  }

  auto full = dir + "/" + file;

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
