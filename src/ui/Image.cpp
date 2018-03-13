/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/Image.hpp>
#include <include/FileManager.hpp>
#include <include/FileNotFound.hpp>
#include <string>

Image::Image(const std::string *filename) {
  loadImage(filename);
}

Image::Image(const std::string *data_filename,
             const std::string *resource_filename) {
  loadImage(data_filename, resource_filename);
}

void Image::loadImage(const std::string *data_filename,
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
    qDebug("User specified image not found; using default");
    // Get path to resource directory image
    path = fm->getResourcePath(*resource_filename);
  }
  QPixmap original(path.c_str());

  // Check that image was loaded; this case should never occur but check anyway
  if (original.isNull()) {
    qFatal("Image could not be loaded: %s\n", path.c_str());
  }
  this->image = original;
}

void Image::loadImage(const std::string *resource_filename) {
  auto *fm = new FileManager();

  // Get path to resource directory image
  std::string path = fm->getResourcePath(*resource_filename);

  QPixmap original(path.c_str());

  // Check that image was loaded; this case should never occur but check anyway
  if (original.isNull()) {
    qFatal("Image could not be loaded: %s\n", path.c_str());
  }
  this->image = original;
}
