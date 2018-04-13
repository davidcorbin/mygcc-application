/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/api/JavaIntegration.hpp>
#include <include/FileNotFound.hpp>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QSettings>
#include <QApplication>
#include <string>
#include <algorithm>
#include <random>
#include <regex> // NOLINT

#define MYGCC_API_FILENAME    "mygcc-api-jar-with-dependencies.jar"
#define VALID_JAVA_VER_REG    "1.8"
#define JAVA_PATH_MAC         "/Library/Internet Plug-Ins/JavaAppletPlugin." \
"plugin/Contents/Home/bin/java"
#define INSTALL_JAVA_SITE     "https://facadeapp.cc/installjava8"

JavaIntegration::JavaIntegration() {
  fm = new FileManager;
}

void JavaIntegration::startAPIThread() {
  auto *initvect = getInitVect();
  auto *enckey = getEncKey();
  qputenv("initvect", initvect->c_str());
  qputenv("enckey", enckey->c_str());
  startAPIServerCmd();
}

void JavaIntegration::startAPIServerCmd() {
  std::string jarPath = fm->getResourcePath(MYGCC_API_FILENAME);

  auto *javaPath = findJava();
  if (!javaPath->empty()) {
    if (checkJavaVersion(javaPath)) {
      qDebug() << "Valid Java version found at" << javaPath->c_str();
      std::string fullStr = "\"" + *javaPath + "\" -cp \""
                            + jarPath + "\" com.mygcc.api.Main";
      qDebug() << "Starting API with command:" << fullStr.c_str();
      javaProcess.start(fullStr.c_str());
    } else {
      qDebug() << "Invalid java version";

      // Open site to show user how to install java
      QDesktopServices::openUrl(QUrl(INSTALL_JAVA_SITE));
    }
  } else {
    qDebug("%s", "Could not start java server");

    // Open site to show user how to install java
    QDesktopServices::openUrl(QUrl(INSTALL_JAVA_SITE));
  }
}

int JavaIntegration::stopAPIServerCmd() {
  javaProcess.close();
  return 0;
}

int JavaIntegration::getAPIPort() {
  return 8080;
}

std::string* JavaIntegration::findJava() {
  // Use the standard path for finding java on macOS
  #if defined(__APPLE__) || defined(__MACH__)
  qDebug() << "Checking for java at known macOS path" << JAVA_PATH_MAC;
  QFileInfo check_file(JAVA_PATH_MAC);
  if (check_file.exists()) {
    qDebug() << "Known macOS java path found";
    return new std::string(JAVA_PATH_MAC);
  } else {
    qDebug() << "Known macOS java path NOT found";
    return new std::string("");
  }
  #endif

  // User registry keys for finding java on Windows
  #if defined(_WIN32) || defined(_WIN64)
  // 64 bit registry key
  QSettings jreKey64("HKEY_LOCAL_MACHINE\\SOFTWARE" \
      "\\JavaSoft\\Java Runtime Environment",
      QSettings::Registry64Format);

  // 32 bit registry key
  QSettings jreKey32("HKEY_LOCAL_MACHINE\\Software\\WOW6432Node" \
      "\\JavaSoft\\Java Runtime Environment",
      QSettings::Registry32Format);

  // If JAVA installed
  if (jreKey32.allKeys().contains("CurrentVersion", Qt::CaseInsensitive) ||
      jreKey64.allKeys().contains("CurrentVersion", Qt::CaseInsensitive)) {
    QSettings *jreKey;

    if (jreKey32.allKeys().contains("CurrentVersion", Qt::CaseInsensitive)) {
      qDebug("32 bit Java FOUND");
      jreKey = &jreKey32;
    }
    if (jreKey64.allKeys().contains("CurrentVersion", Qt::CaseInsensitive)) {
      qDebug("64 bit JAVA FOUND");
      jreKey = &jreKey64;
    }

    auto version = jreKey->value("CurrentVersion").toString();
    qDebug() << "Latest java version identified:" <<
        version.toStdString().c_str();
    if (version.contains("1.8")) {
      QSettings jreVerKey(jreKey->fileName() + "\\" + version,
          QSettings::Registry64Format);

      if (jreVerKey.childKeys().contains("JavaHome", Qt::CaseInsensitive)) {
        auto javaHome = jreVerKey.value("JavaHome").toString();
        qDebug() << "Java home identified:" << javaHome.toStdString().c_str();

        return new std::string(javaHome.toStdString() + "\\bin\\java.exe");
      } else {
        qWarning("JavaHome key NOT FOUND");
      }
    } else {
      qWarning("Java version '1.8' NOT FOUND");
    }
  } else {
    qWarning("Java NOT FOUND in default install path");
  }
  return new std::string("");
  #endif

  #if defined(__unix) || defined(__unix__) || defined(__linux__)
  // Check for java in $PATH
  QProcess findJavaExe;
  findJavaExe.start("java");

  bool started = findJavaExe.waitForStarted();
  QByteArray stdoutput;
  do {
    stdoutput += findJavaExe.readAllStandardOutput();
  } while (!findJavaExe.waitForFinished(100) && findJavaExe.isOpen());

  // If java executable in path
  if (started) {
    return new std::string("java");
  } else {
    return new std::string("");
  }
  #endif
}

bool JavaIntegration::checkJavaVersion(std::string *javaPath) {
  auto *path = new std::string(javaPath->c_str());
  QProcess javaInPath;
  javaInPath.start(("\"" + *path + "\" -version").c_str());
  javaInPath.waitForFinished();
  QString out(javaInPath.readAllStandardError());
  auto output = out.toStdString();

  std::string line(output.begin(),
                   std::find(output.begin(), output.end(), '\n'));
  qDebug("%s", line.c_str());
  std::regex re(VALID_JAVA_VER_REG);
  return std::regex_search(line, re);
}

std::string* JavaIntegration::getInitVect() {
  try {
    QString ivpath = QString::fromStdString(fm->getDataPath("initvect"));
    qDebug() << "Initialization vector path: " << ivpath;
    QFile file(ivpath);
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      std::string line = in.readLine().toStdString();
      file.close();
      return new std::string(line.c_str());
    }
  } catch (FileNotFound &e) {
    // Generate init vect
    auto *initvect = reinterpret_cast<char *>(malloc(sizeof(char) * 17));
    genRandomString(initvect);

    QString datadir = QString::fromStdString(fm->getDataDir());
    QFile file(datadir + "/initvect");
    // Open file
    if (file.open(QIODevice::ReadWrite)) {
      QTextStream stream(&file);
      stream << initvect << endl;
    }
    std::string stdinitvect(initvect);
    return new std::string(stdinitvect.c_str());
  }
  return nullptr;
}

std::string* JavaIntegration::getEncKey() {
  try {
    QString ivpath = QString::fromStdString(fm->getDataPath("enckey"));
    qDebug() << "Encryption key path: " << ivpath;
    QFile file(ivpath);
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      auto line = in.readLine().toStdString();
      file.close();
      return new std::string(line.c_str());
    }
  } catch (FileNotFound &e) {
    // Generate encryption key
    auto *initvect = reinterpret_cast<char *>(malloc(sizeof(char) * 17));
    genRandomString(initvect);

    QString datadir = QString::fromStdString(fm->getDataDir());
    QFile file(datadir + "/enckey");
    // Open file
    if (file.open(QIODevice::ReadWrite)) {
      QTextStream stream(&file);
      stream << initvect << endl;
    }
    std::string stdenckey(initvect);
    return new std::string(stdenckey.c_str());
  }
  return nullptr;
}

void JavaIntegration::genRandomString(char *s, int size) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<> dist(1, 26);

  static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < size; ++i) {
    s[i] = alphanum[static_cast<int>(dist(mt)) % (sizeof(alphanum) - 1)];
  }
  s[size] = 0;
}
