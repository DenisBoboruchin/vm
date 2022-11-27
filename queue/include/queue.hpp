#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace my_containers
{

template <typename T>
class Iqueue 
{
public:
#if 0
    virtual Iqueue () = 0;
    virtual Iqueue (const Iqueue& other) = 0;
    virtual Iqueue (Iqueue&& other) = 0;

    virtual Iqueue& operator= (const Iqueue& other) = 0;
    virtual Iqueue& operator= (Iqueue&& other) = 0;
#endif

    virtual ~Iqueue() {};

#if 1
    virtual void push (T& value) = 0;
    virtual void pop () = 0;

    virtual T& front () = 0;
    virtual T& back () = 0;

    virtual size_t size () = 0;
    virtual bool empty () = 0;
#endif
};

}

#endif
