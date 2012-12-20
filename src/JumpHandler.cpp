#include "JumpHandler.hpp"

JumpHandler::JumpHandler(al5poly::Player & player):
    player_(player)
{
}

void JumpHandler::operator()(
        const std::string &,
        const al5poly::IGameTime & time) const
{
    this->player_.jump(time);
}
