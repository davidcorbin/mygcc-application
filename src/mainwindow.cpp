/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <cpr/cpr.h>
#include <json.hpp>

#include <QDesktopWidget>
#include <QMainWindow>
#include <QLocale>
#include <QWidget>
#include <QLabel>

#include <QPushButton>
#include <QPalette>
#include <QStackedLayout>
#include <QGridLayout>

#include <iostream>

#include "include/mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
        setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        setWindowTitle("Facade");

        QWidget *sidebar = new QWidget();
        sidebar->setStyleSheet("background-color: red");
        // Sidebar width constraints
        sidebar->setMaximumWidth(200);
        sidebar->setMinimumWidth(200);

        // Sidebar height constraints
        sidebar->setMinimumHeight(400);

        QWidget *mainBody = new QWidget();
        mainBody->setStyleSheet("background-color: blue");

        // Body width constraints
        mainBody->setMinimumWidth(400);
        mainBody->setMaximumWidth(800);

        // Body height constraints
        mainBody->setMinimumHeight(400);

        QGridLayout *centralLayout = new QGridLayout;
        centralLayout->addWidget(sidebar, 0, 0, -1, 1);
        centralLayout->addWidget(mainBody, 0, 1, 1, 1);

        QWidget *centralWidget = new QWidget;
        centralWidget->setLayout(centralLayout);
        centralWidget->setStyleSheet("background-color: rgb(50, 48, 52)");

        setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
}
