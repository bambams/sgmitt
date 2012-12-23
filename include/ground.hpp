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
