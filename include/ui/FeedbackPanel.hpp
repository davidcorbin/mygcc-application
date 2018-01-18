/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_FEEDBACKPANEL_HPP_
#define INCLUDE_UI_FEEDBACKPANEL_HPP_

#include <include/ui/SidebarIcon.hpp>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class FeedbackPanel : public QWidget {
 public:
  FeedbackPanel();
  void setup();

 protected:
  void enterEvent(QEvent *event) override;
  void leaveEvent(QEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  QGridLayout *feedbackLayout;
  SidebarIcon *icon;
  QLabel *image_label;
  QLabel *feedbackLabel;
};

#endif  // INCLUDE_UI_FEEDBACKPANEL_HPP_
