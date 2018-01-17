/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/api/JavaIntegration.hpp>
#include <qlogging.h>
#include <include/FileNotFound.hpp>
#include <QFile>
#include <QTextStream>
#include <string>
#include <algorithm>
#include <thread>  // NOLINT
#include <iostream>
#include <random>

#define CLASSPATH_PARAM       "-Djava.class.path="
#define MYGCC_API_FILENAME    "mygcc-api-jar-with-dependencies.jar"

JavaIntegration::JavaIntegration() {
  fm = new FileManager;
}

void JavaIntegration::startAPIThread() {
  char *initvect = getInitVect();
  char *enckey = getEncKey();
  setenv("initvect", initvect, 0);
  setenv("enckey", enckey, 0);
  std::thread t(&JavaIntegration::startAPIServer, this);
  t.detach();
}

void JavaIntegration::startAPIServer() {
  std::string jarPath = fm->getResourcePath(MYGCC_API_FILENAME);

  std::string fullparam = CLASSPATH_PARAM + jarPath;
  auto *writable = new char[fullparam.size() + 1];
  std::copy(fullparam.begin(), fullparam.end(), writable);
  writable[fullparam.size()] = '\0';

  auto* options = new JavaVMOption[1];
  options[0].optionString = writable;
  vm_args.version = JNI_VERSION_1_6;
  vm_args.nOptions = 1;
  vm_args.options = options;
  vm_args.ignoreUnrecognized = JNI_FALSE;

  jlong status = JNI_CreateJavaVM(&jvm,
                                 reinterpret_cast<void**>(&env),
                                 &vm_args);
  if (status == JNI_ERR) {
    qFatal("Unable to load JVM");
  } else if (status == JNI_OK) {
    qDebug("JVM loaded successfully!");
  }
  delete[] options;
  delete[] writable;

  // Find Main class
  jclass cls = env->FindClass("com/mygcc/api/Main");
  if (cls != nullptr) {
    qDebug("mygcc-api class loaded");
  } else {
    env->ExceptionDescribe();
    qFatal("mygcc-api class failed to load");
  }
  // Call public static void main(String[] args)
  jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
  if (mid == nullptr) {
    qDebug("mygcc-api main method not found");
  } else {
    qWarning("mygcc-api main method found");
    env->CallStaticVoidMethod(cls, mid);
  }
}

int JavaIntegration::stopAPIServer() {
  jvm->DestroyJavaVM();
  return 0;
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
