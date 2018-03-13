/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/Schedule.hpp>
#include <string>
#include <vector>

#define SCHEDULE_URL                "http://localhost:8080/1/user/schedule"
#define HTTP_CONTENT_TYPE           "application/json"

Schedule::Schedule(Login *login) : login(login) {
  courses = new std::vector<Course *>();

  connect(login, SIGNAL(authSuccessful()), this, SLOT(queueGetSchedule()));
}

void Schedule::getSchedule(std::string *token) {
  QNetworkRequest request(QUrl(SCHEDULE_URL));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);
  request.setRawHeader("Authorization",
                       (QString::fromStdString(*token)).toUtf8());

  auto *nam = new QNetworkAccessManager;
  QObject::connect(nam, &QNetworkAccessManager::finished,
                   [=](QNetworkReply *reply) -> void {
                     if (reply->error()) {
                       // If credentials invalid
                       if (reply->error() ==
                           QNetworkReply::AuthenticationRequiredError) {
                         qDebug("Invalid credentials");
                         return;
                       }
                       qDebug() << "Unexpected error: " << reply->errorString();
                     }
                     auto response = reply->readAll();
                     QJsonDocument loadDoc(QJsonDocument::fromJson(response));

                     // If invalid json object, reset file
                     if (!loadDoc.isArray()) {
                       qDebug("Invalid json response: expected json array");
                       return;
                     }
                     qDebug("Retreived schedule");
                     parseScheduleJson(loadDoc.array());
                   });

  nam->get(request);
}

void Schedule::queueGetSchedule() {
  auto *token = login->getApiToken();
  getSchedule(token);
}

void Schedule::parseScheduleJson(QJsonArray array) {
  QJsonArray::iterator courseIt;
  // For each course
  for (courseIt = array.begin(); courseIt != array.end(); courseIt++) {
    QJsonObject course = courseIt->toObject();
    Course *courseObj = new Course(course);
    courses->push_back(courseObj);
  }
  emit coursesLoaded();
}

std::vector<Course *> *Schedule::getCourses() const {
  return courses;
}

void Schedule::setCourses(std::vector<Course *> *courses) {
  Schedule::courses = courses;
}
