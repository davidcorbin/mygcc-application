/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/ClassroomViewItem.hpp>
#include <include/FileManager.hpp>
#include <include/ui/StudentImage.hpp>
#include <include/ui/Font.hpp>
#include <include/ui/Color.hpp>
#include <string>

#define DEFAULT_PROFILE_IMAGE            "default_user.jpg"

ClassroomViewItem::ClassroomViewItem(Student *student) {
  verticalLayout = new QVBoxLayout;
  verticalLayout->setContentsMargins(0, 0, 0, 0);
  imageLabel = new QLabel;
  nameLabel = new QLabel(student->getName()->c_str());
}

void ClassroomViewItem::setup() {
  auto *fm = new FileManager();
  std::string defImagePath = fm->getResourcePath(DEFAULT_PROFILE_IMAGE);
  auto *studentImage = new StudentImage(new std::string("profile_user.jpg"));
  defImage = studentImage->setup();

  imageLabel->setPixmap(defImage);
  imageLabel->setFixedWidth(409/3);
  imageLabel->setFixedHeight(543/3);
  imageLabel->setScaledContents(true);

  nameLabel->setPalette(Color::text_primary());
  nameLabel->setFont(Font::sidebarItem());
  nameLabel->setAlignment(Qt::AlignCenter);

  verticalLayout->addWidget(imageLabel);
  verticalLayout->setAlignment(imageLabel, Qt::AlignCenter);
  verticalLayout->addWidget(nameLabel, Qt::AlignCenter);

  setLayout(verticalLayout);
}
