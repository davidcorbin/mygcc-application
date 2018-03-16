/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/InfoGrid.hpp>
#include <include/ui/Font.hpp>
#include <include/ui/Color.hpp>
#include <vector>

#define COLUMNS       3

InfoGrid::InfoGrid(std::vector<GridItem*> *items) : items(items) {
  grid = new QGridLayout;
  count = 0;
  setupEmptyLabel();
}

InfoGrid::InfoGrid() {
  items = new std::vector<GridItem *>();
  grid = new QGridLayout;
  grid->setAlignment(Qt::AlignTop);
  count = 0;
}

void InfoGrid::setup() {
  setupGridParams();
  setupEmptyLabel();

  // If there aren't any GridItems to show
  if (items->empty()) {
    grid->addWidget(emptyLabel);
  }

  // Add GridItems
  for (auto &item : *items) {
    addGridItem(item);
  }
  setLayout(grid);
}

void InfoGrid::addGridItem(GridItem *item) {
  // Remove empty label
  emptyLabel->hide();
  grid->removeWidget(emptyLabel);

  // Add widget to Grid
  grid->addWidget(item, count/COLUMNS, count%COLUMNS);
  grid->setAlignment(Qt::AlignTop);
  count+=1;
}

void InfoGrid::setupEmptyLabel() {
  emptyLabel = new QLabel("No items yet");
  emptyLabel->setFont(Font::assignmentName());
  emptyLabel->setPalette(Color::text_primary());
  emptyLabel->setAlignment(Qt::AlignCenter);
}

void InfoGrid::setupGridParams() {
  grid->setAlignment(Qt::AlignTop);
  grid->setSpacing(0);
  grid->setVerticalSpacing(0);
  grid->setContentsMargins(0, 0, 0, 0);
  grid->setAlignment(Qt::AlignVCenter);
}
