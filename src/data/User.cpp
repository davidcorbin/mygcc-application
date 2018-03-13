/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/User.hpp>
#include <string>

#define USER_URL                "http://localhost:8080/1/user/"
#define HTTP_CONTENT_TYPE       "application/json"

User::User(Login *login) : login(login) {
  userRetrieved = false;
  connect(login, SIGNAL(authSuccessful()), this, SLOT(queueGetUser()));
}

void User::getUser(std::string *token) {
  QNetworkRequest request(QUrl(USER_URL));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);
  request.setRawHeader("Authorization",
                       (QString::fromStdString(*token)).toUtf8());

  auto *nam = new QNetworkAccessManager;
  connect(nam, &QNetworkAccessManager::finished,
         [=](QNetworkReply *reply) -> void {
           if (reply->error()) {
             // If credentials invalid
             if (reply->error() ==
                 QNetworkReply::AuthenticationRequiredError) {
               qDebug("Invalid credentials");
               return;
             }
             qDebug() << "Unexpected error: " << reply->errorString();
             return;
           }
           auto response = reply->readAll();
           QJsonDocument loadDoc(QJsonDocument::fromJson(response));

           // If invalid json object, reset file
           if (!loadDoc.isObject()) {
             qDebug("Invalid json response: expected json array");
             return;
           }
           qDebug("Retrieved user");
           parseUserJson(loadDoc.object());
         });

  nam->get(request);
}

void User::queueGetUser() {
  auto *token = login->getApiToken();
  getUser(token);
}

void User::parseUserJson(QJsonObject jsonObject) {
  profile = new Profile(jsonObject);
  userRetrieved = true;
  emit userLoaded();
}

Profile *User::getProfile() const {
  return profile;
}

void User::setProfile(Profile *profile) {
  User::profile = profile;
}

bool User::isUserRetrieved() const {
  return userRetrieved;
}

void User::setUserRetrieved(bool userRetrieved) {
  User::userRetrieved = userRetrieved;
}
