/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/StudentImage.hpp>
#include <include/FileManager.hpp>
#include <include/FileNotFound.hpp>
#include <QImageReader>
#include <string>

#define DEFAULT_USER_IMG                "default_user.jpg"

StudentImage::StudentImage(const std::string *data_filename) {
  loadImage(data_filename, new std::string(DEFAULT_USER_IMG));
}

QImage StudentImage::setup() {
  imageReader->setScaledSize(QSize(409, 543));
  auto image = imageReader->read();
  if (image.isNull()) {
    qFatal("Image is null");
  }
  return image;
}

void StudentImage::loadImage(const std::string *data_filename,
                             const std::string *resource_filename) {
  auto *fm = new FileManager();

  // Try to load image from data directory and then try to load from resource
  // directory
  std::string path;
  try {
    if (data_filename->empty()) {
      throw FileNotFound(new std::string("No image specified"));
    }
    // Get path to data directory image
    path = fm->getDataPath(*data_filename);
  } catch (FileNotFound &exception) {
    // Get path to resource directory image
    path = fm->getResourcePath(*resource_filename);
  }
  imageReader = new QImageReader(path.c_str());

  // Check that image was loaded; this case should never occur but check anyway
  if (imageReader->error()) {
    qFatal("Image could not be loaded: %s\n", path.c_str());
  }
}
