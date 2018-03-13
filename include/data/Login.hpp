/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_DATA_LOGIN_HPP_
#define INCLUDE_DATA_LOGIN_HPP_

#include <QtNetwork>
#include <string>

class Login : public QObject {
  Q_OBJECT

 public:
  Login();
  void login(std::string *username, std::string *password, bool waitForServer);
  std::string* login(std::string *token);
  void testAPIConnection();
  bool isApiConnectionEstablished() const;
  void queueLogin();
  void saveToken(std::string *token);
  std::string *getApiToken() const;

 private:
  std::string *apiToken;
  bool apiConnectionEstablished;
  int connectionAttempts;
  bool loadUserData();
  void createUserDataFile(std::string datapath);
  std::string datapath;

 private slots:  // NOLINT
  void loginWithToken();

 signals:
  void apiRunning();
  void apiNotRunning();
  void authSuccessful();
  void authInvalidCred();
};

#endif  // INCLUDE_DATA_LOGIN_HPP_
