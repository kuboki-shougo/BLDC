#ifndef TASK_HPP
#define TASK_HPP

#include <base.hpp>

template <class T>
class Task : Base
{
  public:
    void initialize(void)
    {
        static_cast<T &>(this)->initialize();
    }

    void process(void)
    {
        static_cast<T &>(this)->process();
    }

    void finalize(void)
    {
        static_cast<T &>(this)->finalize();
    }
};
#endif
