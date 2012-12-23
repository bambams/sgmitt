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

#ifndef RUN_HANDLER_HPP
    #define RUN_HANDLER_HPP

    #include <al5poly/Camera.hpp>
    #include <al5poly/Direction.hpp>
    #include <al5poly/IInputHandler.hpp>
    #include <al5poly/Player.hpp>

class RunHandler;

    #include "H4xDummy.hpp"

class RunHandler:
    public al5poly::IInputHandler
{
    const int screenWidth_;
    const int screenHeight_;

    al5poly::Camera & camera_;
    al5poly::Player & player_;

    H4xDummy & ground_;
public:
    typedef boost::shared_ptr<RunHandler> Ptr;

    RunHandler(
        const int,
        const int,
        al5poly::Camera &,
        al5poly::Player &,
        H4xDummy &);

    void operator()(
            const std::string &,
            const al5poly::IGameTime &) const;
};

#endif
