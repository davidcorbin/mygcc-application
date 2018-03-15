/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/types/Profile.hpp>
#include <string>

Profile::Profile(int id,
                 std::string *degree,
                 std::string *email,
                 std::string *smajor,
                 std::string *name) : id(id),
                                      degree(degree),
                                      email(email),
                                      smajor(smajor),
                                      name(name) {
}

Profile::Profile(QJsonObject jsonObject) {
  id = jsonObject["ID"].toString().toInt();
  degree = new std::string(jsonObject["degree"].toString().toStdString());
  email = new std::string(jsonObject["email"].toString().toStdString());
  smajor = new std::string(jsonObject["major"].toString().toStdString());
  name = new std::string(jsonObject["name_short"].toString().toStdString());
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
  return smajor;
}

void Profile::setMajor(std::string *smajor) {
  Profile::smajor = smajor;
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
