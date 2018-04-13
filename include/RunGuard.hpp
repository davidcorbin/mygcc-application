/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_RUNGUARD_HPP_
#define INCLUDE_RUNGUARD_HPP_

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

class RunGuard {
 public:
  explicit RunGuard(const QString& key);
  ~RunGuard();

  bool isAnotherRunning();
  bool tryToRun();
  void release();

 private:
  const QString key;
  const QString memLockKey;
  const QString sharedmemKey;

  QSharedMemory sharedMem;
  QSystemSemaphore memLock;

  Q_DISABLE_COPY(RunGuard)
};

#endif  // INCLUDE_RUNGUARD_HPP_
