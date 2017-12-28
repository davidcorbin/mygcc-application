QT += core gui widgets

INCLUDEPATH += $$PRO_FILE_PWD/ext/cpr/include/ \
               $$PRO_FILE_PWD/ext/json/src/ \
               $$PRO_FILE_PWD/include/ \

SOURCES = src/main.cpp \
          src/MainWindow.cpp \
          #src/SlackFeedback.cpp \
          src/ProfileImage.cpp \
          src/OS.cpp \
          src/Color.cpp \
          src/FileManager.cpp \
          src/Font.cpp \

HEADERS = include/ProfileImage.hpp \
          include/OS.hpp \
          include/Color.hpp \
          include/FileManager.hpp \
          include/FileNotFound.hpp \
          include/Font.hpp \

TARGET = facade
