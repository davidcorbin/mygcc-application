/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_GRIDITEM_HPP_
#define INCLUDE_UI_GRIDITEM_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

class GridItem : public QWidget {
  Q_OBJECT

 public:
  GridItem(QString *title, QString *subtitle, QPalette color);

 private:
  QString *title;
  QString* subtitle;
  QPalette color;
  QVBoxLayout *boxLayout;
  QLabel *heroLabel;
  QLabel *subtitleLabel;
  static QGraphicsDropShadowEffect* shadowEffect(QObject *parent,
                                                 int blurRadius,
                                                 const char *color = "#444");
};

#endif  // INCLUDE_UI_GRIDITEM_HPP_
