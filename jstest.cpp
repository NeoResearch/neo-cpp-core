#include <iostream>
#include <memory>
#include <optional>

template<class X>
using op = std::optional<X>;

template<class X>
using uptr = std::unique_ptr<X>;

extern "C"
{
   extern int mycrypto(int x);
}

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

   const char* myteststr(char* s_input)
   {
      std::string sinput{ s_input };
      sinput += 'X';
      std::string soutput{ sinput };
      unsigned r = (unsigned)soutput.c_str(); // CAREFUL!
      return (const char*)r;
   }
};

int
main()
{

   //std::cout << "Hello World" << std::endl;
   //std::cout << mytest(10) << std::endl;

   return 0;
}
