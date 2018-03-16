/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_DATA_CHAPEL_HPP_
#define INCLUDE_DATA_CHAPEL_HPP_

#include <include/data/Login.hpp>
#include <string>
#include <vector>

class Chapel : public QObject {
  Q_OBJECT

 public:
  explicit Chapel(Login *login);
  void getChapel(std::string *token);
  int getRequired();
  int getMakeups();
  int getAttended();
  int getRemaining();
  int getSpecial();

 private:
  Login *login;
  bool chapelReceived;
  std::vector<int> *chapelData;

  void parseChapelJson(QJsonObject object);

 public slots:  // NOLINT
  void queueGetChapel();

 signals:  // NOLINT
  void chapelsReceived();
};

#endif  // INCLUDE_DATA_CHAPEL_HPP_
