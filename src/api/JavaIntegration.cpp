/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/api/JavaIntegration.hpp>
#include <include/FileNotFound.hpp>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <string>
#include <algorithm>
#include <random>
#include <regex> // NOLINT

#define MYGCC_API_FILENAME    "mygcc-api-jar-with-dependencies.jar"
#define VALID_JAVA_VER_REG    "1.8"

JavaIntegration::JavaIntegration() {
  fm = new FileManager;
}

void JavaIntegration::startAPIThread() {
  char *initvect = getInitVect();
  char *enckey = getEncKey();
  qputenv("initvect", initvect);
  qputenv("enckey", enckey);
  startAPIServerCmd();
}

void JavaIntegration::startAPIServerCmd() {
  std::string jarPath = fm->getResourcePath(MYGCC_API_FILENAME);

  auto *javaPath = findJava();
  if (!javaPath->empty()) {
    if (checkJavaVersion(javaPath)) {
      qDebug("%s", "Valid Java version found");
      std::string fullStr = javaPath->append(" -cp ")
                            + jarPath + " com.mygcc.api.Main";
      javaProcess.start(fullStr.c_str());
    } else {
      qDebug("%s", "Invalid java version");
    }
  } else {
    qDebug("%s", "Could not start java server");
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
}

bool JavaIntegration::checkJavaVersion(std::string *javaPath) {
  auto *path = new std::string(javaPath->c_str());
  QProcess javaInPath;
  javaInPath.start(path->append(" -version").c_str());
  javaInPath.waitForStarted();

  QByteArray stderror;
  QByteArray stdoutput;

  javaInPath.waitForStarted();
  do {
    stderror += javaInPath.readAllStandardError();
  } while (!javaInPath.waitForFinished(100));

  stderror += javaInPath.readAllStandardError();

  auto out = new QString(stderror);
  auto output = out->toStdString();

  std::string line(output.begin(),
                   std::find(output.begin(), output.end(), '\n'));
  qDebug("%s", line.c_str());
  std::regex re(VALID_JAVA_VER_REG);
  return std::regex_search(line, re);
}

char* JavaIntegration::getInitVect() {
  try {
    QString ivpath = QString::fromStdString(fm->getDataPath("initvect"));
    QFile file(ivpath);
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      QString line = in.readLine();
      file.close();
      return line.toLatin1().data();
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
    return initvect;
  }
  return nullptr;
}

char* JavaIntegration::getEncKey() {
  try {
    QString ivpath = QString::fromStdString(fm->getDataPath("enckey"));
    QFile file(ivpath);
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      QString line = in.readLine();
      file.close();
      return line.toLatin1().data();
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
    return initvect;
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
