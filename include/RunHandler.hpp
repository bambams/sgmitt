#ifndef RUN_HANDLER_HPP
    #define RUN_HANDLER_HPP

    #include <al5poly/Camera.hpp>
    #include <al5poly/Direction.hpp>
    #include <al5poly/IInputHandler.hpp>
    #include <al5poly/Player.hpp>

class RunHandler;

    #include "ground.hpp"

class RunHandler:
    public al5poly::IInputHandler
{
    const int screenWidth_;
    const int screenHeight_;

    al5poly::Camera & camera_;
    al5poly::Player & player_;

    H4xGround & ground_;
public:
    typedef boost::shared_ptr<RunHandler> Ptr;

    RunHandler(
        const int,
        const int,
        al5poly::Camera &,
        al5poly::Player &,
        H4xGround &);

    void operator()(
            const std::string &,
            const al5poly::IGameTime &) const;
};

#endif
