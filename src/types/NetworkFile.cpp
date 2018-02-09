/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/NetworkFile.hpp>

#include <string>

std::string *NetworkFile::getName() const {
  return name;
}

void NetworkFile::setName(std::string *name) {
  NetworkFile::name = name;
}

std::string *NetworkFile::getType() const {
  return type;
}

void NetworkFile::setType(std::string *type) {
  NetworkFile::type = type;
}
