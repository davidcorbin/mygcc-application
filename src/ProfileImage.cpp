/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ProfileImage.hpp>
#include <include/FileManager.hpp>
#include <include/FileNotFound.hpp>

#include <QBitmap>
#include <QPainter>

#include <string>
#include <iostream>

#define DEF_PROF_IMG          "default_profile.jpg"
#define PROFILE_IMG_DIAMETER  40

ProfileImage::ProfileImage(const std::string profileImage) {
  loadImage(profileImage);
}

QPixmap ProfileImage::setUp() {
  cropImage();
  maskImage();
  scaleImage();
  return image;
}

void ProfileImage::loadImage(std::string profileImage) {
  auto *fm = new FileManager();

  // Try to get custom user image; if not found, use default image
  std::string path;
  try {
    // If no image given, throw exception and use default image
    if (profileImage.empty()) {
      throw FileNotFound(new std::string("No profile image given"));
    }

    // Get path to data directory image
    path = fm->getDataPath(profileImage);
  } catch (FileNotFound &exception) {
    // Get path to resource directory image
    path = fm->getResourcePath(DEF_PROF_IMG);
  }
  QPixmap original(path.c_str());

  // Check that image was loaded; this case should never occur but check anyway
  if (original.isNull()) {
    qFatal(path.c_str());
  }
  this->image = original;
}

void ProfileImage::cropImage() {
  int w = image.width();
  int h = image.height();

  QPixmap scaled;
  if (w < h) {
    int dim = w;
    int yval = (h - dim)/2;
    scaled = image.copy(0, yval, dim, dim);
  } else if (w > h) {
    int dim = h;
    int xval = (w - dim)/2;
    scaled = image.copy(xval, 0, dim, dim);
  } else {
    scaled = image;
  }
  this->image = scaled;
}

void ProfileImage::maskImage() {
  QBitmap mask(image.size());
  QPainter painter(&mask);
  mask.fill(Qt::white);
  painter.setBrush(Qt::black);
  painter.drawEllipse(
      QPoint(mask.width()/2, mask.height()/2),
      image.width()/2,
      image.height()/2);
  image.setMask(mask);
}

void ProfileImage::scaleImage() {
  image = image.scaled(PROFILE_IMG_DIAMETER,
                       PROFILE_IMG_DIAMETER,
                       Qt::KeepAspectRatio,
                       Qt::SmoothTransformation);
}
