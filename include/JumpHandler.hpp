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
