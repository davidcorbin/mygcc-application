/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_ASSIGNMENT_HPP_
#define INCLUDE_TYPES_ASSIGNMENT_HPP_

#include <string>

class Assignment {
 public:
  struct Grade {
    std::string *letter_grade;
    double received_score;
    double percent;
    double points;
  };

  Assignment(std::string *assignment_url,
             std::string *course_url,
             std::string *title,
             std::string *duedate,
             std::string *description,
             bool open,
             Grade grade);

  std::string *getAssignment_url() const;
  void setAssignment_url(std::string *assignment_url);
  std::string *getCourse_url() const;
  void setCourse_url(std::string *course_url);
  std::string *getTitle() const;
  void setTitle(std::string *title);
  std::string *getDuedate() const;
  void setDuedate(std::string *duedate);
  std::string *getDescription() const;
  void setDescription(std::string *description);
  bool isOpen() const;
  void setOpen(bool open);
  const Grade &getGrade() const;
  void setGrade(const Grade &grade);

 private:
  std::string *assignment_url;
  std::string *course_url;
  std::string *title;
  std::string *duedate;
  std::string *description;
  bool open;

  Grade grade;
};

#endif  // INCLUDE_TYPES_ASSIGNMENT_HPP_
