#include <lib-neopt-core-js/src/lib-neopt-core-js.cpp>

EMSCRIPTEN_KEEPALIVE
extern "C" const char*
myteststr(const char* cs_in)
{
   std::string s_in(cs_in);
   //append 'x' in the end
   s_in.append('x');
   return s_in.c_str();
}


int
main()
{
   return 0;
}