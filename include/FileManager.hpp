/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef FACADE_APPLICATION_FILEMANAGER_HPP
#define FACADE_APPLICATION_FILEMANAGER_HPP


#include <string>

class FileManager {
public:
  static std::string getDataDir();
  static bool dirExists(std::string directory);
  static std::string getResourcePath(std::string file);
  static std::string getDataPath(std::string file);
  static inline bool fileExists(const std::string& name);
};


#endif //FACADE_APPLICATION_FILEMANAGER_HPP
