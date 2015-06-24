/* Copyright 2012-2015 Joshua Whitley <maximus5684@gmail.com> / Simon Dawson <spdawson@gmail.com>

   This file is part of lcdapi.

   lcdapi is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of
   the License, or (at your option) any later version.

   lcdapi is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with lcdapi.  If not,
   see <http://www.gnu.org/licenses/>. */

#ifndef _LCDAPI_API_LCDMENUITEM_H_
#define _LCDAPI_API_LCDMENUITEM_H_

/**
 * \defgroup menuitems MenuItems
 *  The menu items are the objects that are displayed on the LCD
 *  when the MenuButton is pressed (as defined in /etc/LCDd.conf).
 *  Each of them correspond to a different item type so they have
 *  different properties that can be set. They share some methods,
 *  defined in the LCDMenuItem class.
 */

#include <lcdapi/api/LCDElement.h>
#include <map>

namespace lcdapi {

/** \class LCDMenuItem LCDMenuItem.h "api/LCDMenuItem.h"
 *  \brief Main class for all menu items including menus and submenus.
 *  \ingroup menuitems
 *
 *  All the menu items in this API have LCDMenuItem as their base class. It contains
 *  common methods but it should not be used directly.
 */

class LCDMenuItem : public LCDElement
{
    protected:
        LCDMenuItem(const std::string &id, LCDElement *parent, const std::string &menuItemType);
        LCDMenuItem(const std::string &id, LCDElement *parent, const std::string &menuItemType, const std::string &text);
        std::string _menuItemType;
        std::string _text;
        bool _isHidden;
        std::string _next;
        std::string _prev;
        typedef std::map<std::string, std::string> OptionMap;
        OptionMap _optionsList;
        void setMenuItemOptions(const std::string &options);
        void notifyChanged();

    public:
        /**
         * \brief Sets the visible text for a menu item.
         *
         * Sets the visible text for a menu item.
         * @param text String that the text will be set to.
         */
        void setText(const std::string &text);

        /**
         * \brief Returns the current text of a menu item.
         *
         * Returns the current text for a menu item.
         */
        const std::string& getText() const;

        /**
         * \brief Sets whether the menu item is hidden in the parent menu or not.
         *
         * Sets whether the menu item is hidden in the parent menu or not. If the parent of this item
         * is an LCDClient, this setting determines whether or not this item will be hidden in the main menu.
         * @param hide Boolean indicating whether the item should be hidden (true) or not (false) on the parent menu.
         */
        void isHidden(bool hide);

        /**
         * \brief Sets the id of the menu item to be shown when the Next button is pressed.
         *
         * Sets the id of the menu item to be shown when the Next button is pressed.
         * @param menuId The id of the menu item to be shown.
         */
        void setNext(const std::string &menuId);

        /**
         * \brief Sets the id of the menu item to be shown when the Prev button is pressed.
         *
         * Sets the id of the menu item to be shown when the Prev button is pressed.
         * @param menuId the id of the menu item to be shown.
         */
        void setPrev(const std::string &menuId);
        virtual void valueCallback(const std::string& value) = 0;
};

} // end of lcdapi namespace

#endif
