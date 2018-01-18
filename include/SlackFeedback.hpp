/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_SLACKFEEDBACK_HPP_
#define INCLUDE_SLACKFEEDBACK_HPP_

#include <string>

class SlackFeedback {
 public:
  enum FeedbackType {
    Bug = 0,
    Enhancement = 1
  };
  void sendFeedback(std::string* message, FeedbackType type);

 private:
  std::string getTypeString(FeedbackType type);
};

#endif  // INCLUDE_SLACKFEEDBACK_HPP_
