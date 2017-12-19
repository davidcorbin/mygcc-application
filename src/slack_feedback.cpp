/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <cpr/cpr.h>
#include <json.hpp>

#include <string>

#include "slack_feedback.hpp"

#define SLACK_FEEDBACK_URL  "https://hooks.slack.com/services/T2CBDTS95"\
                            "/B8F8T6S2D/g9WR5NopLcc8Aj1CpGEi7OVw"
#define SLACK_FALLBACK      "Facade Feedback"
#define SLACK_TITLE         "Facade Feedback"
#define SLACK_MSG_COLOR     "#95a5a6"

#define HTTP_CONTENT_TYPE   "application/json"
#define OS_TITLE            "Operating System"

// Sends an HTTP POST request to the Slack webhook API to send feedback.
// Example:
//      SlackFeedback *feedback = new SlackFeedback();
//      feedback->sendFeedback("Issue with application",
//                             "macOS 10.13.2",
//                             "1.2.3",
//                             feedback->Bugs);
void SlackFeedback::sendFeedback(std::string* message,
                                 std::string* os,
                                 std::string* ver,
                                 FeedbackType type) {
    cpr::Post(cpr::Url{SLACK_FEEDBACK_URL},
              cpr::Body{"{'attachments':["\
                            "{'fallback': '" SLACK_FALLBACK "', "\
                            "'title': '" SLACK_TITLE "', "\
                            "'fields': ["\
                                "{'title': 'Type', "\
                                "'value': '" + getTypeString(type) + "',"\
                                "'short': true}, "\
                                "{'title': 'Version', "\
                                "'value': '" + *ver + "', "\
                                "'short': true}, "\
                                "{'title': 'Operating System', "\
                                "'value': '" + *os + "', "\
                                "'short': true}, "\
                                "{'title': 'Log',"\
                                "'value': '" + *message + "',"\
                                "'short': false}"\
                            "],"\
                            "'color': '" SLACK_MSG_COLOR "'}]}"},
              cpr::Header{{"Content-type", HTTP_CONTENT_TYPE}});
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
