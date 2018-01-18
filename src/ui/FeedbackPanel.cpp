/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/FeedbackPanel.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>
#include <string>

FeedbackPanel::FeedbackPanel() {
  feedbackLayout = new QGridLayout;
  icon = new SidebarIcon(new std::string("comment"));
}

void FeedbackPanel::setup() {
  QPixmap iconmap = icon->setup();
  image_label = new QLabel();
  image_label->setPixmap(iconmap);
  image_label->setFixedWidth(22);
  image_label->setStyleSheet("border: none;");

  feedbackLabel = new QLabel("Feedback");
  feedbackLabel->setStyleSheet("border: none;");
  feedbackLabel->setContentsMargins(20, 3, 5, 3);
  feedbackLabel->setPalette(Color::text_secondary());
  feedbackLabel->setFont(Font::sidebarItem());
  feedbackLabel->setContentsMargins(5, 0, 0, 0);

  feedbackLayout->addWidget(image_label, 0, 0);
  feedbackLayout->addWidget(feedbackLabel, 0, 1);
  feedbackLayout->setContentsMargins(20, 5, 10, 5);

  setFixedHeight(55);
  setStyleSheet("border-top:1px solid rgb(40, 40, 45);");
  setLayout(feedbackLayout);
}

void FeedbackPanel::enterEvent(QEvent* event) {
  feedbackLabel->setPalette(Color::text_primary());
  image_label->setPixmap(icon->active);
}

void FeedbackPanel::leaveEvent(QEvent* event) {
  feedbackLabel->setPalette(Color::text_secondary());
  image_label->setPixmap(icon->normal);
}

void FeedbackPanel::mouseReleaseEvent(QMouseEvent *event) {
  feedbackLabel->setPalette(Color::text_selected());
  image_label->setPixmap(icon->selected);
}
