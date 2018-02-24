/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/SlackFeedback.hpp>
#include <include/OS.hpp>
#include <QtNetwork>
#include <string>

#define SLACK_FEEDBACK_URL  "https://hooks.slack.com/services/T2CBDTS95"\
                            "/B8F8T6S2D/g9WR5NopLcc8Aj1CpGEi7OVw"
#define SLACK_FALLBACK      "Facade Feedback"
#define SLACK_TITLE         "Facade Feedback"
#define SLACK_MSG_COLOR     "#95a5a6"

#define HTTP_CONTENT_TYPE   "application/json"

// Sends an HTTP POST request to the Slack webhook API to send feedback.
// Example:
//      SlackFeedback *feedback = new SlackFeedback();
//      feedback->sendFeedback("Issue with application", feedback->Bugs);
void SlackFeedback::sendFeedback(std::string* message, FeedbackType type) {
  auto *ops = new OS;
  std::string *appVersion = ops->appVersion();
  std::string osname = ops->getOSName();

  std::string temp = "{\"attachments\":[{\"fallback\": \"" SLACK_FALLBACK "\","\
    "\"title\": \"" SLACK_TITLE "\", "\
    "\"fields\": ["\
        "{\"title\": \"Type\", "\
        "\"value\": \"" + getTypeString(type) + "\","\
        "\"short\": true}, "\
        "{\"title\": \"Version\", "\
        "\"value\": \"" + *appVersion + "\", "\
        "\"short\": true}, "\
        "{\"title\": \"Operating System\", "\
        "\"value\": \"" + osname + "\", "\
        "\"short\": true}, "\
        "{\"title\": \"Log\","\
        "\"value\": \"" + *message + "\","\
        "\"short\": false}"\
    "],"\
    "\"color\": \"" SLACK_MSG_COLOR "\"}]}";

  auto json = QJsonDocument::fromJson(temp.c_str());

  QNetworkRequest request(QUrl(SLACK_FEEDBACK_URL));
  request.setHeader(QNetworkRequest::ContentTypeHeader, HTTP_CONTENT_TYPE);

  QNetworkAccessManager nam;
  QNetworkReply *reply = nam.post(request, QJsonDocument(json).toJson());
  while (!reply->isFinished()) {
    qApp->processEvents();
  }
  reply->deleteLater();
}

// Converts FeedbackType to a human readable string for display to the API.
std::string SlackFeedback::getTypeString(FeedbackType type) {
  switch (type) {
    case Bug:
      return "Bug";
    case Enhancement:
      return "Enhancement";
    default:
      return "Feedback";
  }
}
