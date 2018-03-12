/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_API_JAVAINTEGRATION_HPP_
#define INCLUDE_API_JAVAINTEGRATION_HPP_

#include <include/FileManager.hpp>
#include <QProcess>
#include <string>

class JavaIntegration {
 public:
  JavaIntegration();
  void startAPIServerCmd();
  int stopAPIServerCmd();
  int getAPIPort();
  void startAPIThread();
  std::string* findJava();
  bool checkJavaVersion(std::string *javaPath);

 private:
  FileManager *fm;
  QProcess javaProcess;

  std::string* getInitVect();
  std::string* getEncKey();
  void genRandomString(char *s, int size = 16);
};


#endif  // INCLUDE_API_JAVAINTEGRATION_HPP_
