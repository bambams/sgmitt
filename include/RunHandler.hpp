#ifndef RUN_HANDLER_HPP
    #define RUN_HANDLER_HPP

    #include <al5poly/Direction.hpp>
    #include <al5poly/IInputHandler.hpp>
    #include <al5poly/Player.hpp>

class RunHandler:
    public al5poly::IInputHandler
{
    al5poly::Player & player_;
public:
    typedef boost::shared_ptr<RunHandler> Ptr;

    RunHandler(al5poly::Player &);

    void operator()(
            const std::string &,
            const al5poly::IGameTime &) const;
};

#endif
