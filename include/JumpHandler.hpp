#ifndef JUMP_HANDLER_HPP
    #define JUMP_HANDLER_HPP

    #include <al5poly/IGameTime.hpp>
    #include <al5poly/Player.hpp>

class JumpHandler;

    #include "IInputHandler.hpp"

class JumpHandler:
    public IInputHandler
{
    al5poly::Player & player_;
public:
    JumpHandler(al5poly::Player &);

    void operator()(const al5poly::IGameTime &) const;
};

#endif
