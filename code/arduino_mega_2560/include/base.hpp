#ifndef BASE_HPP
#define BASE_HPP

class base
{
  private:
	static void *operator new(size_t);
	static void operator delete(void *);
	static void *operator new[](size_t);
	static void operator delete[](void *);
};

#endif
