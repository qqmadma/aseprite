/* ASE - Allegro Sprite Editor
 * Copyright (C) 2001-2010  David Capello
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef WIDGETS_TABS_H_INCLUDED
#define WIDGETS_TABS_H_INCLUDED

#include "jinete/jwidget.h"
#include <vector>

class Tabs;
class Widget;

/**
   Interface used to control notifications from the Tabs widget.
 */
class ITabsHandler
{
public:
  virtual ~ITabsHandler() { }

  // Called when the user presses a mouse button over a tab
  // button & 1  => left click
  // button & 2  => right click
  // button & 4  => middle click
  virtual void clickTab(Tabs* tabs, void* data, int button) = 0;

  // Called when the mouse is over a tab (the data can be null if the
  // mouse just leave all tabs)
  virtual void mouseOverTab(Tabs* tabs, void* data) = 0;
};

/**
   Tabs control.

   Used in ASE to show opened files/sprites.
 */
class Tabs : public Widget
{
  struct Tab
  {
    std::string text;		// Label in the tab
    void* data;			// Opaque pointer to user data
    int width;			// Width of the tab

    Tab(const char* text, void* data)
    {
      this->text = text;
      this->data = data;
      this->width = 0;
    }
  };

public:
  Tabs(ITabsHandler* handler);
  ~Tabs();

  void addTab(const char* text, void* data);
  void removeTab(void* data);

  void setTabText(const char* text, void* data);

  void selectTab(void* data);
  void* getSelectedTab();

  // Returns the ID of the timer used to scroll tabs when buttons are pressed
  int getTimerId();

protected:
  bool msg_proc(JMessage msg);

private:
  Tab* getTabByData(void* data);
  int getMaxScrollX();
  void makeTabVisible(Tab* tab);
  void setScrollX(int scroll_x);
  void calculateHot();
  int calcTabWidth(Tab* tab);

  std::vector<Tab*> m_list_of_tabs;
  Tab *m_hot;
  Tab *m_selected;
  int m_timer_id;
  int m_scroll_x;

  // Buttons to scroll tabs (useful when there are more tabs than visible area)
  Widget* m_button_left;
  Widget* m_button_right;

  // Handler to send notifications
  ITabsHandler* m_handler;
};

#endif
