/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_NETWORKFILE_HPP_
#define INCLUDE_TYPES_NETWORKFILE_HPP_

#include <string>

class NetworkFile {
 public:
  std::string *getName() const;
  void setName(std::string *name);
  std::string *getType() const;
  void setType(std::string *type);

 private:
  std::string *name;
  std::string *type;
};


#endif  // INCLUDE_TYPES_NETWORKFILE_HPP_
