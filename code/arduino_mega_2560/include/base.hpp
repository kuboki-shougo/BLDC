#ifndef BASE_HPP
#define BASE_HPP

class Base
{
  private:
	Base();
	~Base();
	static void *operator new(size_t);
	static void operator delete(void *);
	static void *operator new[](size_t);
	static void operator delete[](void *);
};

#endif
