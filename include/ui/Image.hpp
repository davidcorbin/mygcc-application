/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_IMAGE_HPP_
#define INCLUDE_UI_IMAGE_HPP_

#include <QPixmap>
#include <string>

class Image {
 public:
  explicit Image(const std::string *filename);
  explicit Image(const std::string *data_filename,
                 const std::string *resource_filename);
  virtual QPixmap setup() = 0;

  QPixmap image;

 private:
  void loadImage(const std::string *resource_filename);
  void loadImage(const std::string *data_filename,
                 const std::string *resource_filename);
};


#endif  // INCLUDE_UI_IMAGE_HPP_
