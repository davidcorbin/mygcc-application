/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_SLACK_FEEDBACK_HPP_
#define INCLUDE_SLACK_FEEDBACK_HPP_

#include <string>

class SlackFeedback {
 public:
  enum FeedbackType { Bug, Enhancement };
  void sendFeedback(std::string* message,
                    std::string* os,
                    std::string* ver,
                    FeedbackType type);

 private:
  std::string getTypeString(FeedbackType type);
};

#endif  // INCLUDE_SLACK_FEEDBACK_HPP_
