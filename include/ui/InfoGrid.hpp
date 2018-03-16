/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#ifndef INCLUDE_UI_INFOGRID_HPP_
#define INCLUDE_UI_INFOGRID_HPP_

#include <include/ui/GridItem.hpp>
#include <QWidget>
#include <QGridLayout>
#include <vector>

class InfoGrid : public QWidget {
  Q_OBJECT

 public:
  explicit InfoGrid(std::vector<GridItem*> *items);
  InfoGrid();
  void setup();
  void addGridItem(GridItem *item);

 private:
  std::vector<GridItem*> *items;
  QGridLayout *grid;
  int count;
  QLabel *emptyLabel;

  void setupEmptyLabel();
  void setupGridParams();
};

#endif  // INCLUDE_UI_INFOGRID_HPP_
