#ifndef MAKE_PTR_HPP
    #define MAKE_PTR_HPP

    #include <boost/shared_ptr.hpp>

template<typename T>
boost::shared_ptr<T> make_ptr(T * const ptr)
{
    boost::shared_ptr<T> sptr(ptr);

    return sptr;
}

template<typename T>
boost::shared_ptr<T> make_ptr(T * const ptr, void (*destroy)(T *))
{
    boost::shared_ptr<T> sptr(ptr, destroy);

    return sptr;
}

#endif
