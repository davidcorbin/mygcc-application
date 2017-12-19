#ifndef SLACKFEEDBACK_HPP
#define SLACKFEEDBACK_HPP

class SlackFeedback
{
public:
    enum FeedbackType { Bug, Enhancement };
    void sendFeedback(std::string* message, std::string* os, std::string* ver, FeedbackType type);
    
private:
    std::string getTypeString(FeedbackType type);
};

#endif
