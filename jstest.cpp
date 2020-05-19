#include <emscripten/bind.h>
#include <iostream>
#include <memory>
#include <optional>

#include <neo3-cpp-core/core_imports.h>

using namespace emscripten;

template<class X>
using op = std::optional<X>;

template<class X>
using uptr = std::unique_ptr<X>;

class X
{
public:
   static int myopt()
   {
      op<int> x = std::make_optional(5);

      uptr<int> pi = uptr<int>{ new int(5) };

      if (x && pi)
         return 10;
      else
         return 20;

      // private key (UINT256) + secp256r1 -> pubkey! (compressed ou non-compressed) 03 ou 04... 33bytes (x + lado) .. 64bytes (x,y)
      // pubkey (compressed 33bytes) + protocolo (neo3) => verification script
      // vscript -> scripthash + protocolo (neo3) -> address (base58)!
   }
};

extern "C"
{
   int mytest(int x)
   {
      std::cout << "mytest x=" << x << std::endl;
      int old_x = x;
      x += mycrypto(x);
      std::cout << "after mycrypto x=" << x << " expects '2*old_x+1'=" << (2 * old_x + 1) << " old_x=" << old_x << std::endl;
      std::cout << "myopt returns 10 or 20 (should be 10):" << X::myopt() << std::endl;

      std::cout << "final value squared: " << (x * x) << std::endl;
      return x * x;
   }

   const char* myteststr(char* s_input, size_t s_input_len)
   {
      std::string sinput(s_input, s_input_len);
      sinput += 'X';
      std::string soutput{ sinput };
      unsigned r = (unsigned)soutput.c_str(); // CAREFUL!

      std::string bn1 = "10";
      std::string bn2 = "20";
      std::cout << "calling 'bignum_add' " << bn1 << " " << bn2 << std::endl;

      //EM_ASM_ARGS({
      //   console.log(Pointer_stringify($0));
      //}, bn1.c_str());
      std::cout << "end" << std::endl;

      std::string out = "abcdefabcdef"; // some space
      const char* pstr = out.c_str();

      //std::string bn3 = bignum_add(bn1.c_str(), bn2.c_str());
      std::cout << "output pointer 1 = " << (void*)pstr << std::endl;
      int rsize = bignum_add(bn1.c_str(), bn2.c_str(), pstr);
      std::cout << "output pointer 2 = " << (void*)pstr << std::endl;
      std::cout << "ptr return on bignum_add = '" << rsize << "' -> str NOT DONE '"
                << "'" << std::endl;
      std::string bn3{ pstr };

      std::cout << "BIG3 = " << bn3 << std::endl;
      return (const char*)r;
   }
};

std::string
my_cpp_teststr(std::string a)
{
   return a.append("x");
}

std::string
cpp_bignum_add(std::string a, std::string b)
{
   // calling 'js' implementation (or pure cpp)
   std::string st = "somespacereserved";
   const char* pstr = st.c_str();
   bignum_add(a.c_str(), b.c_str(), pstr); // output on pstr
   std::cout << "ptr return on cpp_bignum_add = " << pstr << std::endl;
   std::string str{ pstr };
   return str;
}

// these methods are provided to the external world (for nodejs, for example)
EMSCRIPTEN_BINDINGS(my_module)
{
   function("my_cpp_teststr", &my_cpp_teststr);
   function("cpp_bignum_add", &cpp_bignum_add);
}

int
main()
{

   //std::cout << "Hello World" << std::endl;
   //std::cout << mytest(10) << std::endl;

   return 0;
}
