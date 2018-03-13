/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_CLASSTIME_HPP_
#define INCLUDE_TYPES_CLASSTIME_HPP_

#include <string>

class ClassTime {
 public:
  ClassTime(std::string *dayOfWeek,
            std::string *startTime,
            std::string *endTime);
  enum DaysOfWeek {
    U,
    M,
    T,
    W,
    R,
    F,
    S
  };
  DaysOfWeek dayOfWeek;

  std::string *startTime;
  std::string *endTime;
};

#endif  // INCLUDE_TYPES_CLASSTIME_HPP_
