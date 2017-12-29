/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ProfilePanel.hpp>

#include <include/Font.hpp>
#include <include/Color.hpp>

#include <string>
#include <iostream>

ProfilePanel::ProfilePanel(std::string *nameStr,
                           std::string *majorStr,
                           std::string *filename) {
  profImg = new QLabel;
  nameLabel = new QLabel(QString::fromStdString(*nameStr));
  majorLabel = new QLabel(QString::fromStdString(*majorStr));
  profTextLayout = new QVBoxLayout;
  profTextWidget = new QWidget;
  profileLayout = new QGridLayout;

  setName(nameStr);
  setMajor(majorStr);
  setProfileImage(filename);
}

void ProfilePanel::setup() {
  setFixedHeight(65);
  setStyleSheet("border-bottom:1px solid rgb(40, 40, 45);");

  if (imageFile) {
    profileImage = new ProfileImage(imageFile->c_str());
  } else {
    profileImage = new ProfileImage();
  }
  QPixmap scal = profileImage->setUp();

  profImg->setPixmap(scal);
  profImg->setStyleSheet("border-bottom: none;");
  profImg->setMaximumWidth(60);
  profImg->setContentsMargins(10, 0, 10, 0);

  nameLabel->setPalette(Color::text_primary());
  nameLabel->setStyleSheet("border-bottom: none;");
  nameLabel->setFont(Font::profileName());

  majorLabel->setPalette(Color::text_primary());
  majorLabel->setStyleSheet("border-bottom: none;");
  majorLabel->setFont(Font::profileMajor());

  profTextLayout->addWidget(nameLabel);
  profTextLayout->addWidget(majorLabel);
  profTextLayout->setContentsMargins(0, 0, 0, 0);
  profTextLayout->setSpacing(0);

  profTextWidget->setStyleSheet("border-bottom: none;");
  profTextWidget->setLayout(profTextLayout);

  profileLayout->addWidget(profImg, 0, 0);
  profileLayout->addWidget(profTextWidget, 0, 1);
  setLayout(profileLayout);
}

void ProfilePanel::setName(std::string *nameStr) {
  name = nameStr;

  // Update GUI
  nameLabel->setText(QString::fromStdString(*nameStr));
  nameLabel->repaint();
}

void ProfilePanel::setMajor(std::string *majorStr) {
  major = majorStr;

  // Update GUI
  majorLabel->setText(majorStr->c_str());
  majorLabel->repaint();
}

void ProfilePanel::setProfileImage(std::string *filename) {
  imageFile = filename;
}
