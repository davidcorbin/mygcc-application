/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_API_JAVAINTEGRATION_HPP_
#define INCLUDE_API_JAVAINTEGRATION_HPP_

#include <jni.h>

class JavaIntegration {
 public:
  void startAPIServer();
  int stopAPIServer();
  int getAPIPort();
  void startAPIThread();

 private:
  JavaVM *jvm;
  JNIEnv *env;
  JavaVMInitArgs vm_args;
};


#endif  // INCLUDE_API_JAVAINTEGRATION_HPP_
