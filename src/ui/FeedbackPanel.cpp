/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/FeedbackPanel.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>
#include <QPainter>
#include <include/SlackFeedback.hpp>
#include <string>

#define FEEDBACK_TITLE      "Feedback"
#define FEEDBACK_SUBTITLE   "Your opinions matter to us.\nPlease help us " \
                            "make this app better by sending\nfeedback " \
                            "on your experience."
#define FEEDBACK_PLHOLDER   "Please put your feedback here."

FeedbackPanel::FeedbackPanel() {
  feedbackLayout = new QVBoxLayout;
}

void FeedbackPanel::setup() {
  title = new QLabel(FEEDBACK_TITLE);
  title->setPalette(Color::text_primary());
  title->setAlignment(Qt::AlignCenter);
  title->setFont(Font::startupTitle());
  title->setContentsMargins(10, 10, 10, 5);

  subtitle = new QLabel(FEEDBACK_SUBTITLE);
  subtitle->setPalette(Color::text_secondary());
  subtitle->setAlignment(Qt::AlignCenter);
  subtitle->setFont(Font::startupSubtitle());
  subtitle->setContentsMargins(10, 5, 10, 10);

  dropdown = new QComboBox;
  dropdown->addItem("Bug/Issue");
  dropdown->addItem("Feature Request/Idea");
  dropdown->setMaximumWidth(500);
  dropdown->setMinimumWidth(400);
  dropdown->setMinimumHeight(30);
  dropdown->setStyleSheet("background:#fff;color:#000;border-radius:5px;");
  dropdown->setFont(Font::feedbackTextbox());
  dropdown->setContentsMargins(10, 5, 10, 5);

  textbox = new QPlainTextEdit;
  textbox->setStyleSheet("background: #fff; border-radius: 5px; padding: 5px;");
  textbox->setPlaceholderText(FEEDBACK_PLHOLDER);
  textbox->setMaximumWidth(500);
  textbox->setMinimumWidth(400);
  textbox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  textbox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  submitButton = new QPushButton("Submit");
  submitButton->setStyleSheet("background: rgb(182, 45, 214);"
                              "border-radius: 18px;"
                              "padding: 10px 30px;"
                              "color: #fff;");
  submitButton->setMaximumWidth(150);
  submitButton->setContentsMargins(0, 0, 0, 0);
  connect(submitButton, SIGNAL(clicked()), this, SLOT(submitClicked()));

  feedbackLayout->addWidget(title);
  feedbackLayout->setAlignment(title, Qt::AlignCenter);
  feedbackLayout->addWidget(subtitle);
  feedbackLayout->setAlignment(subtitle, Qt::AlignCenter);
  feedbackLayout->addWidget(dropdown, Qt::AlignCenter);
  feedbackLayout->setAlignment(dropdown, Qt::AlignCenter);
  feedbackLayout->addWidget(textbox);
  feedbackLayout->setAlignment(textbox, Qt::AlignCenter);
  feedbackLayout->addWidget(submitButton);
  feedbackLayout->setAlignment(submitButton, Qt::AlignCenter);
  feedbackLayout->setAlignment(Qt::AlignCenter);
  setLayout(feedbackLayout);
}

void FeedbackPanel::paintEvent(QPaintEvent *) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FeedbackPanel::submitClicked() {
  QString textboxData = textbox->toPlainText();
  std::string dataStr = textboxData.toStdString();

  // Do nothing if textbox is empty
  if (textboxData.isEmpty()) {
    return;
  }

  auto *slackfeedback = new SlackFeedback;
  switch (dropdown->currentIndex()) {
    case 1:
      slackfeedback->sendFeedback(&dataStr, slackfeedback->Enhancement);
      break;
    default:
      slackfeedback->sendFeedback(&dataStr, slackfeedback->Bug);
      break;
  }

  // Remove text from text box
  textbox->clear();
}
