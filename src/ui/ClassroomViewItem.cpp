/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/ClassroomViewItem.hpp>
#include <include/FileManager.hpp>
#include <include/ui/StudentImage.hpp>
#include <include/ui/Font.hpp>
#include <include/ui/Color.hpp>
#include <string>

ClassroomViewItem::ClassroomViewItem(Student *student) : student(student) {
  verticalLayout = new QVBoxLayout;
  verticalLayout->setContentsMargins(0, 0, 0, 0);
  imageLabel = new QLabel;
  nameLabel = new QLabel(student->getName()->c_str());
}

void ClassroomViewItem::setup() {
  updateImage();

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

void ClassroomViewItem::updateImage() {
  auto relImgPath = new std::string(std::string("imgcache/") +
                                    std::to_string(student->getId()) + ".jpg");
  auto *studentImage = new StudentImage(relImgPath);
  QImage defImage = studentImage->setup();
  imageLabel->setPixmap(QPixmap::fromImage(defImage));
}
