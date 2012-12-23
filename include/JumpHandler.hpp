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

#ifndef JUMP_HANDLER_HPP
    #define JUMP_HANDLER_HPP

    #include <al5poly/IGameTime.hpp>
    #include <al5poly/IInputHandler.hpp>
    #include <al5poly/Player.hpp>

class JumpHandler:
    public al5poly::IInputHandler
{
    al5poly::Player & player_;
public:
    JumpHandler(al5poly::Player &);

    void operator()(
            const std::string &,
            const al5poly::IGameTime &) const;
};

#endif
