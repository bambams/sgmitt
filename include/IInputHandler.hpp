#ifndef INPUT_HANDLER_HPP
    #define INPUT_HANDLER_HPP

    #include <boost/shared_ptr.hpp>
    #include <boost/weak_ptr.hpp>
    #include <list>

    #include <al5poly/IGameTime.hpp>

class IInputHandler;

class IInputHandler
{
public:
    typedef boost::shared_ptr<IInputHandler> Ptr;
    typedef std::list<Ptr> List;

    virtual ~IInputHandler(void) = 0;

    virtual void operator()(const al5poly::IGameTime &) const = 0;
};

#endif
