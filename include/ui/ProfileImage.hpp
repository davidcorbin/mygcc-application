/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_PROFILEIMAGE_HPP_
#define INCLUDE_UI_PROFILEIMAGE_HPP_

#include <QPixmap>

#include <string>

class ProfileImage {
  QPixmap image;

 public:
  explicit ProfileImage(std::string profileImage = "");
  QPixmap setUp();

 private:
  void cropImage();
  void loadImage(std::string profileImage);
  void maskImage();
  void scaleImage();
};


#endif  // INCLUDE_UI_PROFILEIMAGE_HPP_
