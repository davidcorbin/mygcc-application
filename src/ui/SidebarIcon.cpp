/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/SidebarIcon.hpp>
#include <include/FileManager.hpp>
#include <QSvgRenderer>
#include <QApplication>
#include <QPainter>
#include <QScreen>
#include <string>

#define ICON_DIMENSIONS   20

std::string SidebarIcon::loadIcon(const std::string *filename) {
  auto *fm = new FileManager();

  std::string path;
  // Get path to resource directory image
  path = fm->getResourcePath(*filename);
  return path;
}

QPixmap SidebarIcon::setup() {
  auto const *iconsize = new QSize(22, 22);

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
