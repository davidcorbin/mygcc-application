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
  scheduleRetrieved = false;

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
           qDebug() << "Error: " << reply->errorString();
           emit internalServerError();
           return;
         }
         auto response = reply->readAll();
         QJsonDocument loadDoc(QJsonDocument::fromJson(response));

         // If invalid json object, reset file
         if (!loadDoc.isArray()) {
           qDebug("Invalid json response: expected json array");
           return;
         }
         qDebug("Retrieved schedule");
         parseScheduleJson(loadDoc.array());
       });

  nam->get(request);
}

void Schedule::queueGetSchedule() {
  auto *token = login->getApiToken();
  getSchedule(token);
}

void Schedule::parseScheduleJson(QJsonArray array) {
  // For each course
  foreach(const QJsonValue & value, array) {
    QJsonObject course = value.toObject();
    Course *courseObj = new Course(course);
    courses->push_back(courseObj);
  }
  scheduleRetrieved = true;
  emit coursesLoaded();
}

std::vector<Course *> *Schedule::getCourses() const {
  return courses;
}

void Schedule::setCourses(std::vector<Course *> *courses) {
  Schedule::courses = courses;
}

bool Schedule::isScheduleRetrieved() const {
  return scheduleRetrieved;
}

void Schedule::setScheduleRetrieved(bool scheduleRetrieved) {
  Schedule::scheduleRetrieved = scheduleRetrieved;
}
