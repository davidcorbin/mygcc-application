QT += core gui widgets svg

INCLUDEPATH += $$PRO_FILE_PWD/ext/cpr/include/ \
               $$PRO_FILE_PWD/ext/json/src/ \
               $$PRO_FILE_PWD/include/ \

SOURCES = src/main.cpp \
          src/OS.cpp \
          src/FileManager.cpp \
          #src/SlackFeedback.cpp \
          src/types/Course.cpp \
          src/ui/Color.cpp \
          src/ui/Font.cpp \
          src/ui/Image.cpp \
          src/ui/MainWindow.cpp \
          src/ui/ProfileImage.cpp \
          src/ui/ProfilePanel.cpp \
          src/ui/SidebarIcon.cpp \
          src/ui/SidebarLabel.cpp \
          src/ui/SidebarListItem.cpp \
          src/ui/SidebarPanel.cpp \
          src/ui/LoginPanel.cpp \
          src/ui/LoginButton.cpp \
          src/ui/InfoGrid.cpp \
          src/ui/GridItem.cpp \

HEADERS = include/OS.hpp \
          include/FileManager.hpp \
          include/FileNotFound.hpp \
          #include/slack_feedback.hpp \
          include/types/Course.hpp \
          include/ui/Color.hpp \
          include/ui/Font.hpp \
          include/ui/Image.hpp \
          include/ui/MainWindow.hpp \
          include/ui/ProfileImage.hpp \
          include/ui/ProfilePanel.hpp \
          include/ui/SidebarIcon.hpp \
          include/ui/SidebarLabel.hpp \
          include/ui/SidebarListItem.hpp \
          include/ui/SidebarPanel.hpp \
          include/ui/LoginPanel.hpp \
          include/ui/LoginButton.hpp \
          include/ui/InfoGrid.hpp \
          include/ui/GridItem.hpp \

TARGET = facade
