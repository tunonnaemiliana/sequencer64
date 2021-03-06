/*
 *  This file is part of seq24/sequencer64.
 *
 *  seq24 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  seq24 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with seq24; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          qt5_helpers.cpp
 *
 *  This module declares/defines some helpful macros or functions.
 *
 * \library       sequencer64 application
 * \author        Seq24 team; modifications by Chris Ahlstrom
 * \date          2018-03-14
 * \updates       2018-06-27
 * \license       GNU GPLv2 or above
 *
 */

#include <QPushButton>

#include "qt5_helpers.hpp"

/*
 * Don't document the namespace.
 */

namespace seq64
{

/**
 *  Clears the text of the QPushButton, and sets its icon to the pixmap given
 *  by the pixmap character array.
 *
 * \param pixmap_array
 *      Provides the character array representing the XPM pixmap.
 *
 * \param button
 *      Provides a pointer to the button to be cleared and to have its icon
 *      set.
 */

void
qt_set_icon (const char * pixmap_array [], QPushButton * button)
{
    QPixmap pixmap(pixmap_array);
    QIcon icon;
    icon.addPixmap(pixmap, QIcon::Normal, QIcon::On);
    button->setText("");
    button->setIcon(icon);
}

}               // namespace seq64

/*
 * qt5_helpers.cpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

