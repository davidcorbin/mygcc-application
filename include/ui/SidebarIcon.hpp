/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_SIDEBARICON_HPP_
#define INCLUDE_UI_SIDEBARICON_HPP_

#include <include/ui/Image.hpp>
#include <QPixmap>
#include <string>

class SidebarIcon {
 public:
  explicit SidebarIcon(const std::string *filename) : svgFilename(filename) {}

  QPixmap setup();
  QPixmap normal;
  QPixmap active;
  QPixmap selected;

 private:
  std::string loadIcon(const std::string *filename);
  QPixmap scaleImage(QPixmap original);
  QPixmap FromSvgToPixmap(const QSize &ImageSize, const QString &SvgFile);
  const std::string *svgFilename;
};


#endif  // INCLUDE_UI_SIDEBARICON_HPP_
