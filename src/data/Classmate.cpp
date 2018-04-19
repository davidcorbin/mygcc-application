/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/data/Classmate.hpp>
#include <string>
#include <vector>
#include <algorithm>

#define CLASSMATE_URL               "http://localhost:8080/1/class/"
#define HTTP_CONTENT_TYPE           "application/json"
#define MYGCC_BASE                  "https://my.gcc.edu"
#define IMAGE_CACHE_DIR             "/imgcache"

Classmate::Classmate(Login *login) : login(login) {
  classmatesRec = false;
  students = new std::vector<Student *>();
  nam = new QNetworkAccessManager;
  imgDlnam = new QNetworkAccessManager;
  fm = new FileManager();
  setupConnections();
}

Classmate::Classmate() {
  classmatesRec = false;
  students = new std::vector<Student *>();
  nam = new QNetworkAccessManager;
  imgDlnam = new QNetworkAccessManager;
  fm = new FileManager();
  setupConnections();
}

void Classmate::setupConnections() {
  QObject::connect(nam, &QNetworkAccessManager::finished,
                   [=](QNetworkReply *reply) -> void {
                     if (reply->error()) {
                       if (reply->error() ==
                           QNetworkReply::ConnectionRefusedError) {
                         QJsonObject emptyObject;
                         parseClassmatesJson(emptyObject);
                         return;
                       }
                       qDebug() << "Error:" << reply->errorString();
                       return;
                     }
                     auto response = reply->readAll();
                     QJsonDocument loadDoc(QJsonDocument::fromJson(response));

                     // If invalid json object, return
                     if (!loadDoc.isObject()) {
                       qDebug("Invalid json response: expected json object");
                       return;
                     }

                     classmatesRec = true;
                     qDebug() << "Retrieved classmates for" <<
                              courseCode->c_str();
                     parseClassmatesJson(loadDoc.object());
                   });

  QObject::connect(imgDlnam, &QNetworkAccessManager::finished,
                   [=](QNetworkReply *reply) -> void {
    auto reply_url = reply->url().toString().toLower().toStdString();
    unsigned first = reply_url.find_last_of("/");
    unsigned last = reply_url.find("?");
    auto filename = reply_url.substr(first+1, last-first-1);

    auto dd = fm->getDataDir();
    auto imageCacheDir = (new std::string(dd + IMAGE_CACHE_DIR))->c_str();

    // Create image cached directory if it doesn't exist
    QDir dir(imageCacheDir);
    if (!dir.exists()) {
      qDebug() << "Creating image cache directory at:" << imageCacheDir;
      dir.mkdir(imageCacheDir);
    }

    auto imagePath = (new std::string
        (dd + IMAGE_CACHE_DIR + "/" + filename))->c_str();

    QByteArray downloadedData = reply->readAll();
    QFile newImg(imagePath);
    if (newImg.exists()) {
      emit imageDownloaded(new std::string(filename));
      return;
    }
    if (newImg.open(QIODevice::WriteOnly)) {
      newImg.write(downloadedData);
    }
    newImg.close();

    reply->deleteLater();

    emit imageDownloaded(new std::string(filename));
  });
}

void Classmate::loadClassmates(std::string *token, std::string *courseCode) {
  Classmate::courseCode = courseCode;
  std::string cc = std::string(*courseCode);
  std::string url = std::string(CLASSMATE_URL) + cc + "/collaboration";
  QNetworkRequest request(QUrl(url.c_str()));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);
  request.setRawHeader("Authorization",
                       (QString::fromStdString(*token)).toUtf8());
  nam->get(request);
}

void Classmate::parseClassmatesJson(QJsonObject object) {
  auto dataKey = object.take("data");
  if (!dataKey.isArray()) {
    qWarning("Error: JSON array expected");
    return;
  }
  auto collabArray = dataKey.toArray();
  for (const auto& studentObj : collabArray) {
    if (!studentObj.isObject()) {
      qWarning("Error: JSON object expected");
      return;
    }
    auto studentData = studentObj.toObject();

    auto image_url = studentData["image"].toString().toStdString();
    auto isFaculty = studentData["isFaculty"].toBool();
    auto name = studentData["name"].toString().toStdString();
    auto idNum = studentData["id"].toString().toInt();

    downloadImage(new std::string(image_url));

    auto *student = new Student(new std::string(image_url),
                                isFaculty,
                                new std::string(name),
                                idNum);
    students->push_back(student);
  }

  sortClassmates();

  emit classmatesReceived();
}

void Classmate::sortClassmates() {
}

void Classmate::downloadImage(std::string *url) {
  unsigned first = url->find_last_of("/");
  unsigned last = url->find("?");
  auto filename = url->substr(first+1, last-first-1);

  auto imagePath = (new std::string
      (fm->getDataDir() + IMAGE_CACHE_DIR + "/" + filename))->c_str();

  QFile img(imagePath);
  if (img.exists()) {
    emit imageDownloaded(new std::string(filename));
    return;
  }

  auto full_url = QUrl((MYGCC_BASE + *url).c_str());
  QNetworkRequest request(full_url);
  imgDlnam->get(request);
}

Login *Classmate::getLogin() const {
  return login;
}

void Classmate::setLogin(Login *login) {
  Classmate::login = login;
}

std::vector<Student *> *Classmate::getClassmates() const {
  return students;
}
