/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/GridItem.hpp>
#include <stdlib.h>
#include <include/ui/Font.hpp>

GridItem::GridItem(QString *title,
                   QString *subtitle,
                   QPalette color) : title(title),
                                     subtitle(subtitle),
                                     color(color) {
  boxLayout = new QVBoxLayout;
  boxLayout->setSpacing(0);
  boxLayout->setContentsMargins(10, 10, 10, 10);

  heroLabel = new QLabel(*title);
  heroLabel->setStyleSheet(QString("color: #fff;"
                               "border-top-left-radius: 3px;"
                               "border-top-right-radius: 3px;"
                               "background: rgb(%1, %2, %3);").arg(
      color.color(QPalette::Background).red()).arg(
      color.color(QPalette::Background).green()).arg(
      color.color(QPalette::Background).blue()));
  heroLabel->setFont(Font::heroNumber());
  heroLabel->setAlignment(Qt::AlignCenter);
  heroLabel->setContentsMargins(0, 2, 0, 0);

  subtitleLabel = new QLabel(*subtitle);
  subtitleLabel->setStyleSheet(QString("color: #fff;"
                                   "border-bottom-left-radius: 3px;"
                                   "border-bottom-right-radius: 3px;"
                                   "background: rgb(%1, %2, %3);").arg(
      color.color(QPalette::Background).red()).arg(
      color.color(QPalette::Background).green()).arg(
      color.color(QPalette::Background).blue()));
  subtitleLabel->setFont(Font::subtitleLabel());
  subtitleLabel->setAlignment(Qt::AlignCenter);
  subtitleLabel->setContentsMargins(0, 0, 0, 10);

  boxLayout->addWidget(heroLabel, 0);
  boxLayout->addWidget(subtitleLabel, 0);
  setLayout(boxLayout);

  // Create shadow
  setGraphicsEffect(shadowEffect(this, 10, "#222"));
}

QGraphicsDropShadowEffect* GridItem::shadowEffect(QObject *parent,
                                                    int blurRadius,
                                                    const char *color) {
  QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(parent);
  effect->setBlurRadius(blurRadius);
  effect->setColor(QColor(color));
  effect->setOffset(2, 2);
  return effect;
}

void GridItem::enterEvent(QEvent* event) {
  setGraphicsEffect(shadowEffect(this, 5, "#333"));

  heroLabel->setStyleSheet(QString("color: #fff;"
                                       "border-top-left-radius: 3px;"
                                       "border-top-right-radius: 3px;"
                                       "background: rgb(%1, %2, %3);").arg(
      abs(color.color(QPalette::Background).red()-20)).arg(
      abs(color.color(QPalette::Background).green()-20)).arg(
      abs(color.color(QPalette::Background).blue()-20)));

  subtitleLabel->setStyleSheet(QString("color: #fff;"
                                           "border-bottom-left-radius: 3px;"
                                           "border-bottom-right-radius: 3px;"
                                           "background: rgb(%1, %2, %3);").arg(
      abs(color.color(QPalette::Background).red()-20)).arg(
      abs(color.color(QPalette::Background).green()-20)).arg(
      abs(color.color(QPalette::Background).blue()-20)));
}

void GridItem::leaveEvent(QEvent* event) {
  setGraphicsEffect(shadowEffect(this, 10, "#222"));

  heroLabel->setStyleSheet(QString("color: #fff;"
                                       "border-top-left-radius: 3px;"
                                       "border-top-right-radius: 3px;"
                                       "background: rgb(%1, %2, %3);").arg(
      color.color(QPalette::Background).red()).arg(
      color.color(QPalette::Background).green()).arg(
      color.color(QPalette::Background).blue()));

  subtitleLabel->setStyleSheet(QString("color: #fff;"
                                           "border-bottom-left-radius: 3px;"
                                           "border-bottom-right-radius: 3px;"
                                           "background: rgb(%1, %2, %3);").arg(
      color.color(QPalette::Background).red()).arg(
      color.color(QPalette::Background).green()).arg(
      color.color(QPalette::Background).blue()));
}
