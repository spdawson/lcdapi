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

#include <lcdapi/api/LCDMenuItem.h>
#include <sstream>

namespace lcdapi {

using namespace std;

LCDMenuItem::LCDMenuItem(const string &id, LCDElement *parent, const string &menuItemType)
    : LCDElement(id, "menu_add_item", menuItemType, parent),
    _menuItemType(menuItemType),
    _text(),
    _isHidden(false),
    _next(),
    _prev()
{
    _elementDel = "menu_del_item";
}

void LCDMenuItem::setText(const string &text)
{
    _text = text;
    _optionsList["text",text];
    notifyChanged();
}

string LCDMenuItem::getText()
{
    return _text;
}

void LCDMenuItem::isHidden(bool hide)
{
    _isHidden = hide;
    if (hide)
    {
        _optionsList["is_hidden", "true"];
    }
    else
    {
        _optionsList["is_hidden", "false"];
    }
    notifyChanged();
}

void LCDMenuItem::setNext(const string &menuId)
{
    _next = menuId;
    _optionsList["next", menuId];
    notifyChanged();
}

void LCDMenuItem::setPrev(const string &menuId)
{
    _prev = menuId;
    _optionsList["prev", menuId];
    notifyChanged();
}

void LCDMenuItem::setMenuItemOptions(const string &options)
{
    sendCommand("menu_set_item", options);
}

void LCDMenuItem::notifyChanged()
{
    ostringstream options;

    for (OptionMap::const_iterator it = _optionsList.begin();
            it != _optionsList.end(); ++it)
    {
        options << "-"
                << it->first
                << " "
                << it->second
                << " ";
    }
    _optionsList.clear();
    setMenuItemOptions(options);
}

} // end of lcdapi namespace
