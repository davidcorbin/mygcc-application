/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_FEEDBACKPANEL_HPP_
#define INCLUDE_UI_FEEDBACKPANEL_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QPushButton>

class FeedbackPanel : public QWidget {
  Q_OBJECT

 public:
  FeedbackPanel();
  void setup();

 private:
  QVBoxLayout *feedbackLayout;
  QLabel *title;
  QLabel *subtitle;
  QPlainTextEdit *textbox;
  QComboBox *dropdown;
  QPushButton *submitButton;
  void paintEvent(QPaintEvent *) override;

 public slots:  // NOLINT
  void submitClicked();
};

#endif  // INCLUDE_UI_FEEDBACKPANEL_HPP_
