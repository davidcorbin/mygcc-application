/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/api/JavaIntegration.hpp>
#include <include/FileManager.hpp>
#include <qlogging.h>
#include <string>
#include <algorithm>
#include <thread>  // NOLINT
#include <iostream>

#define CLASSPATH_PARAM       "-Djava.class.path="
#define MYGCC_API_FILENAME    "mygcc-api-jar-with-dependencies.jar"

void JavaIntegration::startAPIThread() {
  std::thread t(&JavaIntegration::startAPIServer, this);
  t.detach();
}

void JavaIntegration::startAPIServer() {
  FileManager *fm = new FileManager;
  std::string jarPath = fm->getResourcePath(MYGCC_API_FILENAME);

  std::string fullparam = CLASSPATH_PARAM + jarPath;
  char * writable = new char[fullparam.size() + 1];
  std::copy(fullparam.begin(), fullparam.end(), writable);
  writable[fullparam.size()] = '\0';

  JavaVMOption* options = new JavaVMOption[1];
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
