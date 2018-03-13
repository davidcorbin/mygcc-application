/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_PROFILEIMAGE_HPP_
#define INCLUDE_UI_PROFILEIMAGE_HPP_

#include <include/ui/Image.hpp>
#include <QPixmap>
#include <string>

class ProfileImage : public Image {
 public:
  explicit ProfileImage(std::string *profileImage) : Image(profileImage, new
      std::string("default_user.jpg")) {}
  QPixmap setup() override;

 private:
  void cropImage();
  void maskImage();
  void scaleImage();
};


#endif  // INCLUDE_UI_PROFILEIMAGE_HPP_
