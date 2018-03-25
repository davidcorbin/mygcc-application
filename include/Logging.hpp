/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_LOGGING_HPP_
#define INCLUDE_LOGGING_HPP_

#include <QtGlobal>
#include <QFile>

class Logging {
 public:
  static void customLogger(QtMsgType type,
                           const QMessageLogContext &context,
                           const QString &msg);

 private:
  static void writeLog(const QMessageLogContext &context,
                       QByteArray localMsg,
                       const char* type);
};

#endif  // INCLUDE_LOGGING_HPP_
