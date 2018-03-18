/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/Chapel.hpp>
#include <string>
#include <vector>

#define SCHEDULE_URL                "http://localhost:8080/1/user/chapel"
#define HTTP_CONTENT_TYPE           "application/json"

Chapel::Chapel(Login *login) : login(login) {
  chapelReceived = false;
  chapelData = new std::vector<int>();

  connect(login, SIGNAL(authSuccessful()), this, SLOT(queueGetChapel()));
}

void Chapel::getChapel(std::string *token) {
  QNetworkRequest request(QUrl(SCHEDULE_URL));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);
  request.setRawHeader("Authorization",
                       (QString::fromStdString(*token)).toUtf8());

  auto *nam = new QNetworkAccessManager;
  QObject::connect(nam, &QNetworkAccessManager::finished,
                   [=](QNetworkReply *reply) -> void {
                     if (reply->error()) {
                       qDebug() << "Error: " << reply->errorString();
                       return;
                     }
                     auto response = reply->readAll();
                     QJsonDocument loadDoc(QJsonDocument::fromJson(response));

                     // If invalid json object, return
                     if (!loadDoc.isObject()) {
                       qDebug("Invalid json response: expected json object");
                       return;
                     }
                     qDebug("Retrieved chapel");
                     parseChapelJson(loadDoc.object());
                   });

  nam->get(request);
}

void Chapel::parseChapelJson(QJsonObject object) {
  if (object.contains("required")) {
    int val = object["required"].toInt();
    chapelData->push_back(val);
  }

  if (object.contains("makeups")) {
    int val = object["makeups"].toInt();
    chapelData->push_back(val);
  }

  if (object.contains("attended")) {
    int val = object["attended"].toInt();
    chapelData->push_back(val);
  }

  if (object.contains("remaining")) {
    int val = object["remaining"].toInt();
    chapelData->push_back(val);
  }

  if (object.contains("special")) {
    int val = object["special"].toInt();
    chapelData->push_back(val);
  }

  chapelReceived = true;
  emit chapelsReceived();
}

void Chapel::queueGetChapel() {
  auto *token = login->getApiToken();
  getChapel(token);
}

int Chapel::getRequired() {
  if (chapelData->size() == 5) {
    return chapelData->at(0);
  }
  return 0;
}

int Chapel::getMakeups() {
  if (chapelData->size() == 5) {
    return chapelData->at(1);
  }
  return 0;
}

int Chapel::getAttended() {
  if (chapelData->size() == 5) {
    return chapelData->at(2);
  }
  return 0;
}

int Chapel::getRemaining() {
  if (chapelData->size() == 5) {
    return chapelData->at(3);
  }
  return 0;
}

int Chapel::getSpecial() {
  if (chapelData->size() == 5) {
    return chapelData->at(4);
  }
  return 0;
}
