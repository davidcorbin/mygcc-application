/**
 * Copyright 2018 <David Corbin, Mitchell Harvey>
 */

#include <include/ui/SidebarLabel.hpp>
#include <include/ui/Color.hpp>
#include <include/ui/Font.hpp>

void SidebarLabel::setup() {
  setContentsMargins(20, 3, 5, 3);
  setPalette(Color::text_secondary());
  setFont(Font::sidebarItem());
  setContentsMargins(5, 0, 0, 0);
}
