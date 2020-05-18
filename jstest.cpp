#include <iostream>
#include <optional>
#include <memory>

template <class X>
using op = std::optional<X>;

template <class X>
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

    uptr<int> pi = uptr<int>{new int(5)};

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
    x += mycrypto(x);
    std::cout << "OI: " << x << std::endl;
    std::cout << "opt: " << X::myopt() << std::endl;
    return x * x;
  }
};

int main()
{

  //std::cout << "Hello World" << std::endl;
  //std::cout << mytest(10) << std::endl;

  return 0;
}
