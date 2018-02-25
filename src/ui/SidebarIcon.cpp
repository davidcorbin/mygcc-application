/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/SidebarIcon.hpp>
#include <include/FileManager.hpp>
#include <QSvgRenderer>
#include <QApplication>
#include <QPainter>
#include <QScreen>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <string>

#define ICON_DIMENSIONS   20
#define ICONS_JSON_FILE   "icons.json"

SidebarIcon::SidebarIcon(Course *course) {
  setIcon(course);
}

SidebarIcon::SidebarIcon(const std::string *iconName) {
  svgFilename = iconName;
}

std::string SidebarIcon::loadIcon(const std::string *filename) {
  auto *fm = new FileManager();

  std::string path;
  // Get path to resource directory image
  path = fm->getResourcePath(*filename);
  return path;
}

QPixmap SidebarIcon::setup() {
  auto const *iconsize = new QSize(ICON_DIMENSIONS, ICON_DIMENSIONS);

  // Get normal icon
  std::string npcc = *svgFilename + std::string("_normal.svg");
  std::string normalpath = loadIcon(&npcc);
  normal = FromSvgToPixmap(*iconsize, QString::fromStdString(normalpath));
  normal = scaleImage(normal);

  // Get active icon
  std::string apcc = *svgFilename + std::string("_active.svg");
  std::string activepath = loadIcon(&apcc);
  active = FromSvgToPixmap(*iconsize, QString::fromStdString(activepath));
  active = scaleImage(active);

  // Get selected icon
  std::string spcc = *svgFilename + std::string("_selected.svg");
  std::string selectedpath = loadIcon(&spcc);
  selected = FromSvgToPixmap(*iconsize, QString::fromStdString(selectedpath));
  selected = scaleImage(selected);

  return normal;
}

QPixmap SidebarIcon::scaleImage(QPixmap original) {
  return original.scaled(ICON_DIMENSIONS,
                         ICON_DIMENSIONS,
                         Qt::KeepAspectRatio,
                         Qt::SmoothTransformation);
}

// https://falsinsoft.blogspot.com/2016/04/
// qt-snippet-render-svg-to-qpixmap-for.html
QPixmap SidebarIcon::FromSvgToPixmap(const QSize &ImageSize,
                                     const QString &SvgFile) {
  const qreal PixelRatio = qApp->primaryScreen()->devicePixelRatio();
  QSvgRenderer SvgRenderer(SvgFile);
  QPixmap Image(ImageSize*PixelRatio);
  QPainter Painter;

  Image.fill(Qt::transparent);

  Painter.begin(&Image);
  SvgRenderer.render(&Painter);
  Painter.end();

  Image.setDevicePixelRatio(PixelRatio);
  return Image;
}

// Sets icon file name based on course code. Assumes that the icon exists
// without checking. There should be a different relevant icon for each major.
void SidebarIcon::setIcon(Course *course) {
  std::string *code = course->getCode();

  // Get location of file.
  auto *fm = new FileManager();
  std::string path;
  path = fm->getResourcePath(ICONS_JSON_FILE);

  // Open icons.json file
  QFile file_obj(path.c_str());
  if (!file_obj.open(QIODevice::ReadOnly)) {
    qFatal("Could not open icons.json");
  }


  QTextStream file_text(&file_obj);
  QString json_string;
  json_string = file_text.readAll();
  file_obj.close();
  QByteArray json_bytes = json_string.toLocal8Bit();

  auto json_doc = QJsonDocument::fromJson(json_bytes);

  if (json_doc.isNull()) {
    qFatal("Failed to create JSON doc.");
  }
  if (!json_doc.isObject()) {
    qFatal("JSON is not an object.");
  }

  QJsonObject json_obj = json_doc.object();

  if (json_obj.isEmpty()) {
    qFatal("JSON object is empty.");
  }

  QVariantMap json_map = json_obj.toVariantMap();

  // Remove digits from course code.
  code->erase(
  std::remove_if(code->begin(), code->end(), &isdigit),
  code->end());

  // If class code does not exist, use default icon.
  if (json_map.contains(code->c_str())) {
    std::string str = json_map[code->c_str()].toString().toStdString();
    svgFilename = new std::string(str);
  } else {
    svgFilename = new std::string("home");
  }
}
