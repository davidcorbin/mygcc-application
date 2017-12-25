/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_PROFILE_IMAGE_H
#define FACADE_APPLICATION_PROFILE_IMAGE_H


#include <QPixmap>

class ProfileImage {
  QPixmap image;

public:
  explicit ProfileImage(std::string profileImage = "");
  QPixmap setUp();

private:
  void cropImage();
  void loadImage(std::string profileImage);
  void maskImage();
};


#endif //FACADE_APPLICATION_PROFILE_IMAGE_H
