/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_API_JAVAINTEGRATION_HPP_
#define INCLUDE_API_JAVAINTEGRATION_HPP_

#include <include/FileManager.hpp>
#include <jni.h>

class JavaIntegration {
 public:
  JavaIntegration();
  void startAPIServer();
  int stopAPIServer();
  int getAPIPort();
  void startAPIThread();

 private:
  JavaVM *jvm;
  JNIEnv *env;
  JavaVMInitArgs vm_args;
  FileManager *fm;

  char* getInitVect();
  char* getEncKey();
  void genRandomString(char *s, int size = 16);
};


#endif  // INCLUDE_API_JAVAINTEGRATION_HPP_
