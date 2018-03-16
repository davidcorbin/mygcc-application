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
  grid->setAlignment(Qt::AlignTop);
  grid->setSpacing(0);
  grid->setVerticalSpacing(0);
  grid->setContentsMargins(0, 0, 0, 0);
  count = 0;
}

InfoGrid::InfoGrid() {
  items = new std::vector<GridItem *>();
}

void InfoGrid::setup() {
  //  If there aren't any GridItems to show
  if (items->empty()) {
    auto *emptyLabel = new QLabel("No items yet");
    emptyLabel->setFont(Font::assignmentName());
    emptyLabel->setPalette(Color::text_primary());
    emptyLabel->setAlignment(Qt::AlignCenter);
    grid->addWidget(emptyLabel);
    grid->setAlignment(Qt::AlignVCenter);
  }

  // Add GridItems
  for (auto &item : *items) {
    addGridItem(item);
  }
  setLayout(grid);
}

void InfoGrid::addGridItem(GridItem *item) {
  grid->addWidget(item, count/COLUMNS, count%COLUMNS);
  count+=1;
}
