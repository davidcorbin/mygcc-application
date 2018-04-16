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
  void login(std::string *token);
  void testAPIConnection();
  bool isApiConnectionEstablished() const;
  void queueLogin();
  void saveToken(std::string *token);
  void deleteUserData();
  std::string *getApiToken() const;

 private:
  std::string *apiToken;
  std::string *username;
  std::string *password;
  bool waitForServer;
  bool apiConnectionEstablished;
  int connectionAttempts;
  std::string datapath;
  QNetworkAccessManager* nam;

  bool loadUserData();
  void createUserDataFile(std::string datapath);
  void verifyAPIToken(std::string *token);
  void testConnectionResponse(QNetworkReply *reply);
  void authReplyResponse(QNetworkReply *reply);
  void verifyTokenResponse(QNetworkReply *reply);

 private slots:  // NOLINT
  void loginWithToken();
  void loginRequestHandler(QNetworkReply *reply);

 signals:
  void apiRunning();
  void apiNotRunning();
  void authSuccessful();
  void authInvalidCred();
};

#endif  // INCLUDE_DATA_LOGIN_HPP_
