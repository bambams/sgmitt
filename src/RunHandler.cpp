#include "RunHandler.hpp"

RunHandler::RunHandler(al5poly::Player & player):
    player_(player)
{
}

void RunHandler::operator()(
        const std::string & action,
        const al5poly::IGameTime & time) const
{
    const int RUN_STEP = 30;
    int dx = RUN_STEP;

    if(action == "run-left")
    {
        this->player_.face(al5poly::AL5POLY_DIRECTION_LEFT);
        dx *= -1;
    }
    else if(action == "run-right")
    {
        this->player_.face(al5poly::AL5POLY_DIRECTION_RIGHT);
    }

    this->player_.setX(this->player_.getX() + dx);
}
