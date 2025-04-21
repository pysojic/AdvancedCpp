#include <iostream>
#include "my_promise.h"

using namespace mpcs;

int main()
{
  MyPromise<int> mpi;
  std::thread thr{ [&]() { 
	  try 
      {
		  std::cout << mpi.get_future().get() << std::endl;
	  } 
      catch(std::exception &e) 
      {
		  std::cout << e.what() << std::endl;
	  }}
  };
#if 1
  mpi.set_value(7);
#else
  try {
	  throw runtime_error("Some runtime error");
  }
  catch (exception &) {
	  mpi.set_exception(current_exception());
  }
#endif
  thr.join();
  return 0;
}
