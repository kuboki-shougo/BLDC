#ifndef BASE_HPP
#define BASE_HPP

class base
{
  private:
	base();
	~base();
	static void *operator new(size_t);
	static void operator delete(void *);
	static void *operator new[](size_t);
	static void operator delete[](void *);
};

#endif
