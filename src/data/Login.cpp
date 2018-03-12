/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/Login.hpp>
#include <include/FileManager.hpp>
#include <include/FileNotFound.hpp>
#include <QObject>
#include <string>

#define API_URL_BASE             "http://localhost:8080/"
#define AUTH_URL                 "http://localhost:8080/1/auth/"
#define MAX_CONN_ATTEMPTS        1000
#define HTTP_CONTENT_TYPE        "application/json"
#define USER_DATA_FILE           "userdata.json"
#define API_TOKEN_KEY            "api_token"

Login::Login() {
  apiConnectionEstablished = false;
  connectionAttempts = 0;
  loadUserData();
}

void Login::login(std::string *username,
                  std::string *password,
                  bool waitForServer) {
  // Fail if the server it not running and not waiting for server
  if (!isApiConnectionEstablished() && !waitForServer) {
    emit apiNotRunning();
  }

  std::string temp = "{\"username\": \"" + *username + "\", \"password\": \""
                     + *password + "\"}";
  auto json = QJsonDocument::fromJson(temp.c_str());

  QNetworkRequest request(QUrl(AUTH_URL));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);

  auto *nam = new QNetworkAccessManager;

  QObject::connect(nam, &QNetworkAccessManager::finished,
          [=](QNetworkReply *reply) -> void {
            if (reply->error()) {
              // If credentials invalid
              if (reply->error() ==
                  QNetworkReply::AuthenticationRequiredError) {
                qDebug("Invalid credentials");
                emit authInvalidCred();
                return;
              }

              // If waiting for server to start
              if (waitForServer) {
                qDebug() << "Network error: " << reply->errorString();
                return login(username, password, waitForServer);
              }

              qDebug() << "Unexpected error: " << reply->errorString();
            }
            qDebug("Valid credentials");
            emit authSuccessful();

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

            // Save token
            saveToken(&tokenStr);
          });

  QNetworkReply *reply = nam->post(request, QJsonDocument(json).toJson());
  while (!reply->isFinished()) {
    qApp->processEvents();
  }
  reply->deleteLater();
}

std::string* Login::login(std::string *token) {
  qDebug() << "Login called with token" << QString::fromStdString(*token);
}

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
  auto *networkAccessManager = new QNetworkAccessManager;
  QObject::connect(networkAccessManager,
                   &QNetworkAccessManager::finished,
                   [=](QNetworkReply *reply) {
                     if (reply->error()) {
                       apiConnectionEstablished = false;
                       // Limit connection attempts
                       if (connectionAttempts < MAX_CONN_ATTEMPTS) {
                         connectionAttempts += 1;
                         testAPIConnection();
                       }
                       return;
                     }
                     qDebug("API connection established");
                     apiConnectionEstablished = true;
                     emit apiRunning();
                   });
  QNetworkRequest networkRequest(QUrl(API_URL_BASE));
  networkAccessManager->get(networkRequest);
}

bool Login::isApiConnectionEstablished() const {
  return apiConnectionEstablished;
}

//
// Loads username and password from a file if they exist.
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
      qDebug("Invalid user data file");
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
    qWarning("User data file invalid");
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
