/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/Updater.hpp>
#include <include/OS.hpp>
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QXmlStreamReader>
#include <QCoreApplication>
#include <QNetworkReply>
#include <string>

#define MAINTEN_EXE_MAC        "/../../../FacadeMaintenance.app/Contents/" \
"MacOS/FacadeMaintenance"
#define MAINT_EXE_MAC_UPD      "/../../../FacadeMaintenance.app/Contents/" \
"MacOS/FacadeMaintenance  --silentUpdate"
#define MAINTEN_EXE_WIN        "/FacadeMaintenance.exe"
#define MAINT_EXE_WIN_UPD      "/FacadeMaintenance.exe --silentUpdate"
#define MAC_COMPON_REL_PATH    "/../../../Components.xml"
#define WIN_COMPON_REL_PATH    "/components.xml"
#define UBU_COMPON_REL_PATH    "/components.xml"

#define REM_MAC_UPD_XML_URL     "http://facade-logs.appspot.com/repo/mac/" \
"Updates.xml"
#define REM_WIN_UPD_XML_URL     "http://facade-logs.appspot.com/repo/win/" \
"Updates.xml"
#define REM_UBU_UPD_XML_URL     "http://facade-logs.appspot.com/repo/ubuntu/" \
"Updates.xml"

Updater::Updater() {
  osname = OS::getOSName();
  nam = new QNetworkAccessManager(this);
}

void Updater::checkForUpdates() {
  if (maintenanceToolExists()) {
    qDebug("Maintenance tool FOUND");

    auto *installedVer = installedVersion();
    if (installedVer->empty()) {
      qWarning("Installed components version NOT FOUND");
      return;
    }

    #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    qInfo() << "Installed components version:" << installedVer->c_str();
    #endif

    installedApplicationVersion = installedVer;

    remoteVersion();
  } else {
    qWarning("Maintenance tool NOT FOUND");
  }
}

void Updater::installUpdates() {
  qApp->quit();
  QProcess::startDetached(QCoreApplication::applicationDirPath() +
                          MAINT_EXE_MAC_UPD);
}

void Updater::remoteVersion() {
  QNetworkRequest request;
  if (osname == "macOSX") {
    request = QNetworkRequest(QUrl(REM_MAC_UPD_XML_URL));
  } else if (osname == "Windows 32-bit" || osname == "Windows 64-bit") {
    request = QNetworkRequest(QUrl(REM_WIN_UPD_XML_URL));
  } else if (osname == "Linux") {
    request = QNetworkRequest(QUrl(REM_UBU_UPD_XML_URL));
  }

  QObject::connect(nam, &QNetworkAccessManager::finished,
          [=](QNetworkReply *reply) -> void {
            if (reply->error()) {
              qDebug() << "Error: " << reply->errorString();
              return;
            }
            auto response = reply->readAll();

            std::string version;
            auto *xmlReader = new QXmlStreamReader(response);

            while (!xmlReader->atEnd() && !xmlReader->hasError()) {
              QXmlStreamReader::TokenType token = xmlReader->readNext();
              if (token == QXmlStreamReader::StartDocument) {
                continue;
              }
              if (token == QXmlStreamReader::StartElement) {
                if (xmlReader->name() == "Version") {
                  version = xmlReader->readElementText().toStdString();
                }
              }
            }

            if (xmlReader->hasError()) {
              qWarning("Error parsing retrieved xml");
            }
            xmlReader->clear();

            if (version.empty()) {
              qWarning("Version string NOT FOUND");
            }

            remoteApplicationVersion = new std::string(version);
            #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
            qInfo() << "Remote components version:" <<
                    remoteApplicationVersion->c_str();
            #endif

            if (*installedApplicationVersion != *remoteApplicationVersion) {
              #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
              qInfo("Installed application version is NOT equal to remote" \
              " application version");
              #endif
              installUpdates();
            } else {
              #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
              qInfo("Application up to date");
              #endif
            }
          });

  nam->get(request);
}

std::string* Updater::installedVersion() {
  return new std::string(OS::appVersion()->substr(1));
}

bool Updater::maintenanceToolExists() {
  QFileInfo check_file;
  if (osname == "macOSX") {
    check_file = QFileInfo(QCoreApplication::applicationDirPath() +
                           MAINTEN_EXE_MAC);
  } else if (osname == "Windows 32-bit" || osname == "Windows 64-bit") {
    check_file = QFileInfo(QCoreApplication::applicationDirPath() +
                           MAINTEN_EXE_WIN);
  } else if (osname == "Linux") {
    check_file = QFileInfo(QCoreApplication::applicationDirPath() + "/DNE");
  }

  if (check_file.exists()) {
    return true;
  } else {
    return false;
  }
}
