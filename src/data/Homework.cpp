/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/Homework.hpp>
#include <string>
#include <vector>
#include <algorithm>

#define HOMEWORK_URL                "http://localhost:8080/1/class/"
#define HTTP_CONTENT_TYPE           "application/json"

Homework::Homework(Login *login) : login(login) {
  homeworkRec = false;
  assignments = new std::vector<Assignment *>();
  nam = new QNetworkAccessManager;
}

Homework::Homework() {
  homeworkRec = false;
  assignments = new std::vector<Assignment *>();
  nam = new QNetworkAccessManager;
}

void Homework::getHomework(std::string *token, std::string *courseCode) {
  Homework::courseCode = courseCode;
  std::string cc = std::string(*courseCode);
  std::string url = std::string(HOMEWORK_URL) + cc + "/homework";
  QNetworkRequest request(QUrl(url.c_str()));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);
  request.setRawHeader("Authorization",
                       (QString::fromStdString(*token)).toUtf8());

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

                     homeworkRec = true;
                     qDebug() << "Retrieved homework for" <<
                                                           courseCode->c_str();
                     parseHomeworkJson(loadDoc.object());
                   });
  nam->get(request);
}

void Homework::parseHomeworkJson(QJsonObject object) {
  auto sectionTitles = object.keys();
  for (const auto& sectionName : sectionTitles) {
    auto sectionGrades = object[sectionName];
    if (!sectionGrades.isArray()) {
      qWarning("Error: JSON array expected");
      return;
    }
    auto sectionGradeArray = sectionGrades.toArray();
    for (const auto& assignmentW : sectionGradeArray) {
      auto assignmentObj = assignmentW.toObject();

      auto a_url = assignmentObj["assignment_url"].toString().toStdString();
      auto c_url = assignmentObj["course_url"].toString().toStdString();
      auto a_title = assignmentObj["title"].toString().toStdString();
      auto a_duedate = assignmentObj["due"].toString().toStdString();
      auto a_desc = assignmentObj["description"].toString().toStdString();
      auto a_open = false;
      if (assignmentObj["open"].toBool()) {
        a_open = true;
      }
      auto grades = assignmentObj["grade"].toObject();
      auto a_letter = new std::string("");
      auto a_received = 0.0;
      auto a_percent = 0.0;
      auto a_points = 0.0;
      if (grades.contains("letter")) {
        a_letter = new std::string(grades["letter"].toString().toStdString());
      }
      if (grades.contains("received")) {
        auto val = grades["received"].toString().toStdString();
        try {
          a_received = std::stod(val);
        } catch (const std::invalid_argument& ia) {
          qWarning() << "Could not convert " << val.c_str() << " to double";
        }
      }
      if (grades.contains("percent")) {
        auto val = grades["percent"].toString().toStdString();
        try {
          a_percent = std::stod(val);
        } catch (const std::invalid_argument& ia) {
          qWarning() << "Could not convert " << val.c_str() << " to double";
        }
      }
      if (grades.contains("points")) {
        auto val = grades["points"].toString().toStdString();
        try {
          a_points = std::stod(val);
        } catch (const std::invalid_argument& ia) {
          qWarning() << "Could not convert " << val.c_str() << " to double";
        }
      }
      auto *assignment = new Assignment(new std::string(a_url.c_str()),
                                        new std::string(c_url.c_str()),
                                        new std::string(a_title.c_str()),
                                        new std::string(a_duedate.c_str()),
                                        new std::string(a_desc.c_str()),
                                        a_open,
                                        a_letter,
                                        a_received,
                                        a_percent,
                                        a_points);
      assignments->push_back(assignment);
    }
  }

  sortAssignments();

  emit homeworkReceived();
}

void Homework::sortAssignments() {
  std::sort(assignments->begin(), assignments->end(),
            [] (Assignment const *a, Assignment const *b) {
              auto *aa = new QString(a->getDuedate()->c_str());
              auto aTemp = QDateTime::fromString(*aa, Qt::ISODate);

              auto *bb = new QString(b->getDuedate()->c_str());
              auto bTemp = QDateTime::fromString(*bb, Qt::ISODate);

              // If both assignments are open
              if (a->isOpen() && b->isOpen()) {
                if (!aTemp.isValid() || !bTemp.isValid()) {
                  return false;
                }
                if (aTemp > bTemp) {
                  return true;
                } else {
                  return false;
                }
              } else if (!a->isOpen() && !b->isOpen()) {  // Both closed
                if (!aTemp.isValid() || !bTemp.isValid()) {
                  return false;
                }
                return true;
              } else if (a->isOpen() && !b->isOpen()) {  // A open, B closed
                return true;
              } else if (!a->isOpen() && b->isOpen()) {  // A closed, B open
                return false;
              }
              return false;
            });
}

Login *Homework::getLogin() const {
  return login;
}

void Homework::setLogin(Login *login) {
  Homework::login = login;
}

std::vector<Assignment *> *Homework::getAssignments() const {
  return assignments;
}
