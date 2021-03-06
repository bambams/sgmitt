/*
 * sgmitt is a Christmas themed platformer video game.
 * Copyright (C) 2012 Brandon McCaig
 *
 * This file is part of sgmitt.
 *
 * sgmitt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * sgmitt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with sgmitt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "H4xDummy.hpp"

H4xDummy::H4xDummy(
        int x,
        int y,
        const al5poly::ALLEGRO_BITMAP_Ptr sprite):
    x_(x),
    y_(y),
    sprite_(sprite)
{
}

int H4xDummy::getWidth(void) const
{
    return al_get_bitmap_width(this->sprite_.get());
}

int H4xDummy::getX(void) const
{
    return this->x_;
}

int H4xDummy::getY(void) const
{
    return this->y_;
}

int H4xDummy::setX(const int x)
{
    return this->x_ = x;
}

int H4xDummy::setY(const int y)
{
    return this->y_ = y;
}

al5poly::IFrame::Ptr H4xDummy::getCurrentFrame(
        const al5poly::IGameTime &) const
{
    return make_ptr(new al5poly::Frame(this->sprite_));
}

al5poly::Orientation H4xDummy::getOrientation(void) const
{
    return al5poly::AL5POLY_ORIENTATION_NONE;
}
