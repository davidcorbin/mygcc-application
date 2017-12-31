/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_FILEMANAGER_HPP_
#define INCLUDE_FILEMANAGER_HPP_


#include <string>

class FileManager {
 public:
  static std::string getDataDir();
  static bool dirExists(std::string directory);
  static std::string getResourcePath(std::string file);
  static std::string getDataPath(std::string file);
  static inline bool fileExists(const std::string& name);
};

#endif  // INCLUDE_FILEMANAGER_HPP_
