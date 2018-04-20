/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_STUDENTIMAGE_HPP_
#define INCLUDE_UI_STUDENTIMAGE_HPP_

#include <include/ui/Image.hpp>
#include <QImageReader>
#include <string>

class StudentImage {
 public:
  explicit StudentImage(const std::string *data_filename);
  QImage setup();

 private:
  QImageReader *imageReader;

  void loadImage(const std::string *data_filename,
                 const std::string *resource_filename);
};

#endif  // INCLUDE_UI_STUDENTIMAGE_HPP_
