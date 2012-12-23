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

#ifndef GROUND_HPP
    #define GROUND_HPP

    #include <al5poly/altypedef.hpp>
    #include "al5poly/Frame.hpp"
    #include "al5poly/IFrame.hpp"
    #include "al5poly/IGameTime.hpp"
    #include <al5poly/IRenderable.hpp>
    #include <al5poly/Orientation.hpp>

class H4xGround;

    #include "make_ptr.hpp"

class H4xGround:
    public al5poly::IRenderable
{
    int x_;
    int y_;
    const al5poly::ALLEGRO_BITMAP_Ptr sprite_;
public:
    H4xGround(int, int, const al5poly::ALLEGRO_BITMAP_Ptr);

    int getWidth(void) const;
    int getX(void) const;
    int getY(void) const;

    int setX(const int);
    int setY(const int);

    al5poly::IFrame::Ptr getCurrentFrame(
            const al5poly::IGameTime &) const;

    al5poly::Orientation getOrientation(void) const;
};

#endif
