/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_STUDENTIMAGE_HPP_
#define INCLUDE_UI_STUDENTIMAGE_HPP_

#include <include/ui/Image.hpp>
#include <string>

class StudentImage : public Image {
 public:
  explicit StudentImage(std::string *profileImage) : Image(profileImage, new
      std::string("default_user.jpg")) {}
  QPixmap setup() override;
};

#endif  // INCLUDE_UI_STUDENTIMAGE_HPP_
