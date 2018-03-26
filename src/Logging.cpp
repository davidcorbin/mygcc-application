/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/Logging.hpp>
#include <include/FileManager.hpp>
#include <QApplication>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

#define LOG_FILE            "facade_logs.log"

void Logging::customLogger(QtMsgType type,
                  const QMessageLogContext &context,
                  const QString &msg) {
  QByteArray localMsg = msg.toLocal8Bit();
  switch (type) {
    case QtDebugMsg: {
      fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      writeLog(context, localMsg, "Debug");
      break;
    }

    #if QT_VERSION > QT_VERSION_CHECK(5, 5, 0)
    case QtInfoMsg:
      fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      writeLog(context, localMsg, "Info");
      break;
    #endif

    case QtWarningMsg:
      fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      writeLog(context, localMsg, "Warning");
      break;
    case QtCriticalMsg:
      fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      writeLog(context, localMsg, "Critical");
      break;
    case QtFatalMsg:
      fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(),
              context.file, context.line, context.function);
      writeLog(context, localMsg, "Fatal");
      abort();
  }
}

void Logging::writeLog(const QMessageLogContext &context,
                       QByteArray localMsg,
                       const char* type) {
  auto *fm = new FileManager;
  std::string dataDir = fm->getDataDir() + "/" + LOG_FILE;
  QFile *outFile = new QFile(dataDir.c_str());

  // Truncate if more than 100kb
  if (outFile->size() > 100000) {
    outFile->resize(0);
  }

  outFile->open(QIODevice::WriteOnly | QIODevice::Append);
  QTextStream stream(outFile);
  stream << type << " (" << QDateTime::currentDateTime().toString() << ")"
         << ": " << localMsg.constData() << " (" << context.file << ": "
         << context.line << ") " << context.function << endl;
  outFile->close();
}
