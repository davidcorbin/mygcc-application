/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_DATA_USER_HPP_
#define INCLUDE_DATA_USER_HPP_

#include <include/data/Login.hpp>
#include <include/types/Profile.hpp>
#include <string>

class User : public QObject {
  Q_OBJECT

 public:
  explicit User(Login *login);
  void getUser(std::string *token);
  void parseUserJson(QJsonObject jsonObject);
  Profile *getProfile() const;
  void setProfile(Profile *profile);
  bool isUserRetrieved() const;
  void setUserRetrieved(bool userRetrieved);

 private:
  Login *login;
  Profile *profile;

  bool userRetrieved;

 private slots:  // NOLINT
  void queueGetUser();

 signals:
  void userLoaded();
};

#endif  // INCLUDE_DATA_USER_HPP_
