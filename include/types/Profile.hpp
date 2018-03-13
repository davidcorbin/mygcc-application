/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_TYPES_PROFILE_HPP_
#define INCLUDE_TYPES_PROFILE_HPP_

#include <QJsonObject>
#include <string>

class Profile {
 public:
  Profile(int id,
          std::string *degree,
          std::string *email,
          std::string *major,
          std::string *name);
  explicit Profile(QJsonObject jsonObject);
  int getId() const;
  void setId(int id);
  std::string *getDegree() const;
  void setDegree(std::string *degree);
  std::string *getEmail() const;
  void setEmail(std::string *email);
  std::string *getMajor() const;
  void setMajor(std::string *major);
  std::string *getName() const;
  void setName(std::string *name);
  std::string *getImage_url() const;
  void setImage_url(std::string *image_url);

 private:
  int id;
  std::string *degree;
  std::string *email;
  std::string *major;
  std::string *name;
  std::string *image_url;
};


#endif  // INCLUDE_TYPES_PROFILE_HPP_
