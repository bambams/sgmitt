#include "RunHandler.hpp"

RunHandler::RunHandler(
        const int screenWidth,
        const int screenHeight,
        al5poly::Camera & camera,
        al5poly::Player & player,
        H4xGround & ground):
    screenWidth_(screenWidth),
    screenHeight_(screenHeight),
    camera_(camera),
    player_(player),
    ground_(ground)
{
}

void RunHandler::operator()(
        const std::string & action,
        const al5poly::IGameTime & time) const
{
    const int CAMERA_FOLLOW = 200;
    const int RUN_STEP = 30;

    // This doesn't make sense until velocity plays a role so the player
    // continues to move forward in the air...
    //if(!this->player_.isLanded())
    //{
    //    return;
    //}

    int cx = this->camera_.getX();
    int dx = RUN_STEP;
    int gx = this->ground_.getX();
    int px = this->player_.getX();

    // h4x...
    static int cd = cx - px;
    static int gd = gx - px;

    if(action == "run-left")
    {
        this->player_.face(al5poly::AL5POLY_DIRECTION_LEFT);
        dx *= -1;
    }
    else if(action == "run-right")
    {
        this->player_.face(al5poly::AL5POLY_DIRECTION_RIGHT);
    }

    px += dx;

    this->player_.setX(px);

    cx -= cd;

    int diff = cx > px ? cx - px : px - cx;

    if(diff > CAMERA_FOLLOW)
    {
        cx = cx + dx + cd;

        this->camera_.setX(cx);
    }

    gx = px + gd;

    this->ground_.setX(gx);
}
