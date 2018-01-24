/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/CourseAssignmentItem.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>
#include <QHBoxLayout>

CourseAssignmentItem::CourseAssignmentItem(Course *course) : course(course) {
}

void CourseAssignmentItem::setup() {
  auto *gradeString = new QString("A+");
  auto *gradeLabel = setupLetterLabel(gradeString);

  auto *pointsString = new QString("8/8");
  auto *pointsLabel = setupGradeLabel(pointsString);

  auto *nameString = new QString("Celebration of Learning 5");
  auto *assignmentNameLabel = setupNameLabel(nameString);

  auto *dueDateString = new QString("Monday, December 11 at 5 pm");
  auto *dueDateLabel = setupDueDateLabel(dueDateString);

  auto *textDivider = new QVBoxLayout;
  textDivider->addWidget(assignmentNameLabel);
  textDivider->setAlignment(assignmentNameLabel,
                            Qt::AlignRight|Qt::AlignBottom);
  textDivider->addWidget(dueDateLabel);
  textDivider->setAlignment(dueDateLabel,
                            Qt::AlignRight|Qt::AlignTop);
  textDivider->setContentsMargins(0, 0, 0, 0);

  auto *assignmentData = new QWidget;
  assignmentData->setLayout(textDivider);

  auto *assignmentLayout = new QHBoxLayout;
  assignmentLayout->addWidget(gradeLabel);
  assignmentLayout->addWidget(pointsLabel);
  assignmentLayout->addWidget(assignmentData);
  assignmentLayout->setAlignment(assignmentData, Qt::AlignRight);

  setStyleSheet("background:rgb(40,39,45);");
  setContentsMargins(0, 0, 0, 0);
  setLayout(assignmentLayout);
}

QLabel* CourseAssignmentItem::setupLetterLabel(QString *letterStr) {
  auto font = Font::assignmentGrade();
  auto *gradeLabel = new QLabel(letterStr->toLatin1());
  gradeLabel->setPalette(Color::assignment_green());
  gradeLabel->setFont(font);
  // Set font width to text size + margin
  QFontMetrics fm(font);
  gradeLabel->setMaximumWidth(fm.width(letterStr->toLatin1()) + 10);
  return gradeLabel;
}

QLabel* CourseAssignmentItem::setupGradeLabel(QString *gradeStr) {
  auto font = Font::assignmentPoints();
  auto *gradeLabel = new QLabel(gradeStr->toLatin1());
  gradeLabel->setPalette(Color::text_secondary());
  gradeLabel->setFont(font);
  // Set font width to text size + margin
  QFontMetrics fm(font);
  gradeLabel->setMaximumWidth(fm.width(gradeStr->toLatin1()) + 10);
  return gradeLabel;
}

QLabel* CourseAssignmentItem::setupNameLabel(QString *nameStr) {
  auto font = Font::assignmentName();
  auto *gradeLabel = new QLabel(nameStr->toLatin1());
  gradeLabel->setPalette(Color::text_primary());
  gradeLabel->setFont(font);
  // Set font width to text size + margin
  QFontMetrics fm(font);
  gradeLabel->setMaximumWidth(fm.width(nameStr->toLatin1()) + 10);
  return gradeLabel;
}

QLabel* CourseAssignmentItem::setupDueDateLabel(QString *dueDateStr) {
  auto font = Font::assignmentDueDate();
  auto *gradeLabel = new QLabel(dueDateStr->toLatin1());
  gradeLabel->setPalette(Color::text_secondary());
  gradeLabel->setFont(font);
  // Set font width to text size + margin
  QFontMetrics fm(font);
  gradeLabel->setMaximumWidth(fm.width(dueDateStr->toLatin1()) + 10);
  return gradeLabel;
}
