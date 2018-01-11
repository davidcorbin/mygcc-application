/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/InfoGrid.hpp>
#include <vector>

#define COLUMNS       3

InfoGrid::InfoGrid(std::vector<GridItem*> *items) : items(items) {
  grid = new QGridLayout;
  grid->setAlignment(Qt::AlignTop);
  grid->setSpacing(0);
  grid->setVerticalSpacing(0);
  grid->setContentsMargins(0, 0, 0, 0);
  count = 0;
}

void InfoGrid::setup() {
  for (auto &item : *items) {
    addGridItem(item);
  }
  setLayout(grid);
}

void InfoGrid::addGridItem(GridItem *item) {
  grid->addWidget(item, count/COLUMNS, count%COLUMNS);
  count+=1;
}
