/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/Login.hpp>
#include <include/FileManager.hpp>
#include <include/FileNotFound.hpp>
#include <QObject>
#include <QMessageBox>
#include <string>

#define API_URL_BASE             "http://localhost:8080/"
#define AUTH_URL                 "http://localhost:8080/1/auth/"
#define AUTH_URL_VERIFY          "http://localhost:8080/1/auth/verify"
#define MAX_CONN_ATTEMPTS        1000
#define HTTP_CONTENT_TYPE        "application/json"
#define USER_DATA_FILE           "userdata.json"
#define API_TOKEN_KEY            "api_token"

Login::Login() {
  nam = new QNetworkAccessManager(this);
  apiConnectionEstablished = false;
  connectionAttempts = 0;
  loadUserData();

  connect(nam, SIGNAL(finished(QNetworkReply*)), this,
          SLOT(loginRequestHandler(QNetworkReply*)));
}

void Login::login(std::string *username,
                  std::string *password,
                  bool waitForServer) {
  // Fail if the server it not running and not waiting for server
  if (!isApiConnectionEstablished() && !waitForServer) {
    emit apiNotRunning();
  }

  this->username = username;
  this->password = password;
  this->waitForServer = waitForServer;

  std::string temp = "{\"username\": \"" + *username + "\", \"password\": \""
                     + *password + "\"}";
  auto json = QJsonDocument::fromJson(temp.c_str());

  QNetworkRequest request(QUrl(AUTH_URL));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);

  QNetworkReply *reply = nam->post(request, QJsonDocument(json).toJson());
  reply->setProperty("login", QVariant("authReply"));
}

//
// Login with API token.
//
void Login::login(std::string *token) {
  qDebug() << "Login called with token" << QString::fromStdString(*token);
  verifyAPIToken(token);
}

//
// Handle network responses for network access manager.
//
void Login::loginRequestHandler(QNetworkReply *reply) {
  QString property = reply->property("login").toString();

  if (property == "testAPIConnReply") {
    testConnectionResponse(reply);
  } else if (property == "authReply") {
    authReplyResponse(reply);
  } else if (property == "verifyTokenReply") {
    verifyTokenResponse(reply);
  }
}

//
// Queue the logging with the token until the api is running.
//
void Login::queueLogin() {
  QObject::connect(this, SIGNAL(apiRunning()), this, SLOT(loginWithToken()));
}

void Login::loginWithToken() {
  login(apiToken);
}

//
// Tests network connection to API.
// Sends GET requests to the API until it gets a response.
//
void Login::testAPIConnection() {
  QNetworkRequest networkRequest(QUrl(API_URL_BASE));
  QNetworkReply *reply = nam->get(networkRequest);
  reply->setProperty("login", QVariant("testAPIConnReply"));
}

void Login::testConnectionResponse(QNetworkReply *reply) {
  if (reply->error()) {
    apiConnectionEstablished = false;
    // Limit connection attempts
    if (connectionAttempts < MAX_CONN_ATTEMPTS) {
      connectionAttempts += 1;
      QThread::msleep(500);  // Sleep for half a second between requests
      testAPIConnection();
    }
    reply->deleteLater();
    return;
  }
  qDebug("API connection established");
  apiConnectionEstablished = true;
  emit apiRunning();
  reply->deleteLater();
}

void Login::authReplyResponse(QNetworkReply *reply) {
  if (reply->error()) {
    // If credentials invalid
    if (reply->error() == QNetworkReply::AuthenticationRequiredError) {
      qDebug("Invalid credentials");
      emit authInvalidCred();
      return;
    }

    // If waiting for server to start
    if (waitForServer && QNetworkReply::ConnectionRefusedError) {
      qDebug() << "Network error:" << reply->errorString();

      if (apiConnectionEstablished) {
        qWarning("API conn. was established but connection refused. Exiting");
        QMessageBox::critical(nullptr, tr("Error"), tr("Issue connecting to " \
        "API server. Please restart the application."));
        qApp->exit(1);
      }

      reply->deleteLater();

      QThread::msleep(500);

      login(username, password, waitForServer);
      return;
    }

    qDebug() << "Unexpected error:" << reply->errorString();
  } else {
    qDebug("Valid credentials");

    auto response = reply->readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(response));

    // If invalid json object, reset file
    if (!loadDoc.isObject()) {
      qDebug("Invalid json response");
    }

    auto tokenStr = loadDoc.object()
        .value("token")
        .toString()
        .toStdString();

    apiToken = new std::string(tokenStr);
    emit authSuccessful();

    // Save token
    saveToken(&tokenStr);
  }
}

void Login::verifyTokenResponse(QNetworkReply *reply) {
  if (reply->error()) {
    qDebug() << "Invalid token:" << reply->errorString();
    reply->deleteLater();
    return;
  }
  reply->deleteLater();
  qDebug("Valid token");
  emit authSuccessful();
}

bool Login::isApiConnectionEstablished() const {
  return apiConnectionEstablished;
}

//
// Loads username and password from a file if they exist. If they don't exist,
// the method creates a new json file for the credentials.
//
bool Login::loadUserData() {
  auto *fm = new FileManager();
  try {
    datapath = fm->getDataPath(USER_DATA_FILE);
    qDebug("Opening file %s", datapath.c_str());

    QFile userData(datapath.c_str());

    if (!userData.open(QIODevice::ReadOnly)) {
      qWarning("Couldn't open save file.");
      return false;
    }

    QByteArray saveData = userData.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    // If invalid json object, reset file
    if (!loadDoc.isObject()) {
      qDebug("Invalid user data file: expected json object");
      userData.close();
      createUserDataFile(datapath);
    }

    QJsonObject jsonObject = loadDoc.object();
    if (jsonObject.contains(API_TOKEN_KEY)) {
      auto apiTokenStr = jsonObject.value(API_TOKEN_KEY)
          .toString()
          .toStdString();
      apiToken = new std::string(apiTokenStr);
      queueLogin();
      userData.close();
      return true;
    } else {
      userData.close();
      qDebug("No token found");
    }
  } catch (FileNotFound &e) {
    datapath = fm->getDataDir() + "/" + USER_DATA_FILE;
    createUserDataFile(datapath);
  }
  return false;
}

//
// Deletes the userdata file, logging user out.
//
void Login::deleteUserData() {
  if (!datapath.empty()) {
    QFile file(datapath.c_str());
    file.remove();
  }
}

//
// Create user data json file.
//
void Login::createUserDataFile(std::string datapath) {
  QFile saveFile(datapath.c_str());

  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }

  QJsonObject gameObject;
  QJsonDocument saveDoc(gameObject);
  saveFile.write(saveDoc.toJson());

  saveFile.close();

  qDebug("File created at %s", datapath.c_str());
}

//
// Save token to user data file.
//
void Login::saveToken(std::string *token) {
  QFile saveFile(datapath.c_str());

  if (!saveFile.open(QIODevice::ReadWrite)) {
    qWarning("Couldn't open save file.");
    return;
  }

  QByteArray saveData = saveFile.readAll();
  QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

  // If invalid json object, reset file
  if (!loadDoc.isObject()) {
    qWarning("User data file invalid: expected json object");
    saveFile.close();
    createUserDataFile(datapath);
  }

  saveFile.close();
  saveFile.open(QIODevice::ReadWrite | QIODevice::Truncate);

  auto jsonObject = loadDoc.object();
  jsonObject[API_TOKEN_KEY] = QString::fromStdString(*token);
  QJsonDocument saveDoc(jsonObject);
  saveFile.write(saveDoc.toJson());
  saveFile.close();

  qDebug("Saved token");
}

std::string *Login::getApiToken() const {
  return apiToken;
}

void Login::verifyAPIToken(std::string *token) {
  // Fail if the server it not running and not waiting for server
  if (!isApiConnectionEstablished()) {
    qDebug("API not running");
    emit apiNotRunning();
  }

  QNetworkRequest request(QUrl(AUTH_URL_VERIFY));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);
  request.setRawHeader("Authorization",
                       (QString::fromStdString(*token)).toUtf8());

  QNetworkReply *reply = nam->get(request);
  reply->setProperty("login", QVariant("verifyTokenReply"));
}
