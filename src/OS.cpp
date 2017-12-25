/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <OS.hpp>

#include <string>

std::string OS::getOSName() {
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __unix || __unix__
  return "Unix";
  #elif __APPLE__ || __MACH__
  return "macOSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #else
  return "Other";
  #endif
}
