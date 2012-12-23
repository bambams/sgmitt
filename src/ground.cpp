#include "ground.hpp"

H4xGround::H4xGround(
        int x,
        int y,
        const al5poly::ALLEGRO_BITMAP_Ptr sprite):
    x_(x),
    y_(y),
    sprite_(sprite)
{
}

int H4xGround::getWidth(void) const
{
    return al_get_bitmap_width(this->sprite_.get());
}

int H4xGround::getX(void) const
{
    return this->x_;
}

int H4xGround::getY(void) const
{
    return this->y_;
}

int H4xGround::setX(const int x)
{
    return this->x_ = x;
}

int H4xGround::setY(const int y)
{
    return this->y_ = y;
}

al5poly::IFrame::Ptr H4xGround::getCurrentFrame(
        const al5poly::IGameTime &) const
{
    return make_ptr(new al5poly::Frame(this->sprite_));
}

al5poly::Orientation H4xGround::getOrientation(void) const
{
    return al5poly::AL5POLY_ORIENTATION_NONE;
}
