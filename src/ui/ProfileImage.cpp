/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/ProfileImage.hpp>

#include <QBitmap>
#include <QPainter>

#define PROFILE_IMG_DIAMETER  40

QPixmap ProfileImage::setup() {
  cropImage();
  maskImage();
  scaleImage();
  return image;
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
