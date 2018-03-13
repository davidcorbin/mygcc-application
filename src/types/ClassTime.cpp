/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/ClassTime.hpp>
#include <QDebug>
#include <string>

ClassTime::ClassTime(std::string *dow, std::string *sTime,
                     std::string *eTime) {
  if (*dow == "M") {
    dayOfWeek = M;
  } else if (*dow == "T") {
    dayOfWeek = T;
  } else if (*dow == "W") {
    dayOfWeek = W;
  } else if (*dow == "R") {
    dayOfWeek = R;
  } else if (*dow == "F") {
    dayOfWeek = F;
  } else if (*dow == "S") {
    dayOfWeek = S;
  } else if (*dow == "U") {
    dayOfWeek = U;
  } else {
    qWarning() << "Error parsing day of week:" << dow;
    dayOfWeek = M;
  }

  startTime = sTime;
  endTime = eTime;
}
