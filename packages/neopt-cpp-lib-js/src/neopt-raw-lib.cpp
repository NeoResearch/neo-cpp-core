#include <neo3-cpp-bindings/neo3-bindings.hpp>
#include <neo3-cpp-core/core_imports.h>






#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
extern "C"
int fib(int n) {
  int i, t, a = 0, b = 1;
  for (i = 0; i < n; i++) {
    t = a + b;
    a = b;
    b = t;
  }
  return b;
}


EMSCRIPTEN_KEEPALIVE
extern "C"
int myoutro(int n) {
  return n+10;
}



int
main()
{

   //std::cout << "Hello World" << std::endl;
   //std::cout << mytest(10) << std::endl;

   return 0;
}
