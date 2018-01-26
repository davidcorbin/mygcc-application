/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Assignment.hpp>
#include <string>

Assignment::Assignment(std::string *assignment_url,
                       std::string *course_url,
                       std::string *title,
                       std::string *duedate,
                       std::string *description,
                       bool open,
                       std::string *letter_grade,
                       double received_score,
                       double percent,
                       double points) : assignment_url(assignment_url),
                                      course_url(course_url),
                                      title(title),
                                      duedate(duedate),
                                      description(description),
                                      open(open) {
  grade.letter_grade = letter_grade;
  grade.received_score = received_score;
  grade.percent = percent;
  grade.points = points;
}

std::string *Assignment::getAssignment_url() const {
  return assignment_url;
}

void Assignment::setAssignment_url(std::string *assignment_url) {
  Assignment::assignment_url = assignment_url;
}

std::string *Assignment::getCourse_url() const {
  return course_url;
}

void Assignment::setCourse_url(std::string *course_url) {
  Assignment::course_url = course_url;
}

std::string *Assignment::getTitle() const {
  return title;
}

void Assignment::setTitle(std::string *title) {
  Assignment::title = title;
}

std::string *Assignment::getDuedate() const {
  return duedate;
}

void Assignment::setDuedate(std::string *duedate) {
  Assignment::duedate = duedate;
}

std::string *Assignment::getDescription() const {
  return description;
}

void Assignment::setDescription(std::string *description) {
  Assignment::description = description;
}

bool Assignment::isOpen() const {
  return open;
}

void Assignment::setOpen(bool open) {
  Assignment::open = open;
}

const Assignment::Grade &Assignment::getGrade() const {
  return grade;
}

void Assignment::setGrade(const Assignment::Grade &grade) {
  Assignment::grade = grade;
}
