/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_PROFILEPANEL_HPP_
#define INCLUDE_UI_PROFILEPANEL_HPP_

#include <include/ui/ProfileImage.hpp>

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <string>

class ProfilePanel : public QWidget {
 public:
  ProfilePanel(std::string *nameStr,
               std::string *majorStr,
               std::string *filename = nullptr);
  void setName(std::string *nameStr);
  void setMajor(std::string *majorStr);
  void setProfileImage(std::string *filename);
  void setup();

 private:
  std::string *name;
  std::string *major;
  std::string *imageFile;
  QGridLayout *profileLayout;
  QWidget *profTextWidget;
  QVBoxLayout *profTextLayout;
  QLabel *majorLabel;
  QLabel *nameLabel;
  QLabel *profImg;
  ProfileImage *profileImage;
};


#endif  // INCLUDE_UI_PROFILEPANEL_HPP_
