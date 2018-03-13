/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Profile.hpp>
#include <string>

Profile::Profile(int id,
                 std::string *degree,
                 std::string *email,
                 std::string *major,
                 std::string *name) : id(id),
                                      degree(degree),
                                      email(email),
                                      major(major),
                                      name(name) {
}

Profile::Profile(QJsonObject jsonObject) {
  id = jsonObject["ID"].toString().toInt();
  degree = new std::string(jsonObject["degree"].toString().toStdString());
  email = new std::string(jsonObject["email"].toString().toStdString());
  major = new std::string(jsonObject["major"].toString().toStdString());
  name = new std::string(jsonObject["name"].toString().toStdString());
}

int Profile::getId() const {
  return id;
}

void Profile::setId(int id) {
  Profile::id = id;
}

std::string *Profile::getDegree() const {
  return degree;
}

void Profile::setDegree(std::string *degree) {
  Profile::degree = degree;
}

std::string *Profile::getEmail() const {
  return email;
}

void Profile::setEmail(std::string *email) {
  Profile::email = email;
}

std::string *Profile::getMajor() const {
  return major;
}

void Profile::setMajor(std::string *major) {
  Profile::major = major;
}

std::string *Profile::getName() const {
  return name;
}

void Profile::setName(std::string *name) {
  Profile::name = name;
}

std::string *Profile::getImage_url() const {
  return image_url;
}

void Profile::setImage_url(std::string *image_url) {
  Profile::image_url = image_url;
}
