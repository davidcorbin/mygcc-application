/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/CourseAssignmentItem.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>
#include <QHBoxLayout>
#include <cmath>
#include <string>

CourseAssignmentItem::CourseAssignmentItem(Assignment *assignment) :
    assignment(assignment) {
}

void CourseAssignmentItem::setup() {
  auto *gradeString = new QString(assignment->getGrade().letter_grade->data());
  auto *gradeLabel = setupLetterLabel(gradeString);

  auto *pointsString = new QString(getPointsString().c_str());
  auto *pointsLabel = setupGradeLabel(pointsString);

  auto *nameString = new QString(assignment->getTitle()->c_str());
  auto *assignmentNameLabel = setupNameLabel(nameString);

  auto *dueDateString = new QString(assignment->getDuedate()->c_str());
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

std::string CourseAssignmentItem::getPointsString() {
  double receivedScore = assignment->getGrade().received_score;
  double totalPoints = assignment->getGrade().points;

  std::string receivedStr = getReadablePoints(receivedScore);
  std::string totalStr = getReadablePoints(totalPoints);

  std::string pointsStringText = receivedStr + "/" + totalStr;
  return pointsStringText;
}

std::string CourseAssignmentItem::getReadablePoints(double points) {
  double wholeNum;
  double decimal = std::modf(points, &wholeNum);

  // If the value is an int (no decimal places)
  if (decimal == 0) {
    return std::to_string(static_cast<int>(wholeNum));
  } else {  // If there is a decimal
    std::string pointsString = std::to_string(points);
    return pointsString.erase(pointsString.find_last_not_of('0') + 1,
                              std::string::npos);
  }
}