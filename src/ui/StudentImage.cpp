/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/StudentImage.hpp>

QPixmap StudentImage::setup() {
  return image.scaled(409, 543, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
