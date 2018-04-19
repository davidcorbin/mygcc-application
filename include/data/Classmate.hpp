/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_DATA_CLASSMATE_HPP_
#define INCLUDE_DATA_CLASSMATE_HPP_

#include <include/data/Login.hpp>
#include <include/types/Student.hpp>
#include <include/FileManager.hpp>
#include <string>
#include <vector>

class Classmate : public QObject {
  Q_OBJECT

 public:
  /**
   * Constructor that sets login.
   * @param login login object
   */
  explicit Classmate(Login *login);

  /**
   * Constructor without login.
   */
  Classmate();

  void loadClassmates(std::string *token, std::string *courseCode);

  std::vector<Student *> *getClassmates() const;

  /**
   * Get login object.
   * @return login object
   */
  Login *getLogin() const;

  /**
   * Set login object.
   * @param login login object
   */
  void setLogin(Login *login);

 private:
  bool classmatesRec;
  std::vector<Student *> *students;
  Login *login;
  std::string *courseCode;
  QNetworkAccessManager *nam;
  QNetworkAccessManager *imgDlnam;
  FileManager *fm;

  void parseClassmatesJson(QJsonObject object);
  void sortClassmates();
  void setupConnections();
  void downloadImage(std::string *url);

 signals:  // NOLINT
  void classmatesReceived();
  void imageDownloaded(std::string *filename);
};

#endif  // INCLUDE_DATA_CLASSMATE_HPP_
