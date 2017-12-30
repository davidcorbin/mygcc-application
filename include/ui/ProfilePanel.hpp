/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_PROFILEPANEL_HPP
#define FACADE_APPLICATION_PROFILEPANEL_HPP

#include "ProfileImage.hpp"

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


#endif //FACADE_APPLICATION_PROFILEPANEL_HPP
