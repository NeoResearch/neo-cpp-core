#pragma once

// -------------------------------------------------------
// these are useful to javascript ONLY (via emscripten)
// ------------------------------------------------------

// =======================================================================================
// these are C++ methods provided to emscripten (js part) via connection on C++ Neo3 Core
//
#include <neo3-cpp-core/Core.hpp>
#include <neo3-cpp-core/core_imports.h>
// ---------------------------------------------------------------------------

#include <iostream>
#include <memory>   // uptr - TODO REMOVE
#include <optional> // uptr - TODO REMOVE

#include <emscripten/bind.h>

#include <emscripten.h>


EMSCRIPTEN_KEEPALIVE
extern "C"
int myoutro_denovo(int n) {
  return n+50;
}


// =======================
// DO NOT DELETE THIS IDEA
// =======================
//EMSCRIPTEN_KEEPALIVE
//extern "C"
//const char* c_API_CreateSignatureRedeemScript(const char* cs_in, char* cs_out) {
//
// this considers that memory is owned by outsider, and return 'cs_out' again
//
// current idea now is to allocate memory locally and return 'char ptr' (could be lost.. we hope not!)
// ===============================================================================

EMSCRIPTEN_KEEPALIVE
extern "C"
const char* c_API_CreateSignatureRedeemScript(const char* cs_in) {
   std::string sin(cs_in);
   std::cout << "PRINT s='" << sin << "'" << std::endl;
   std::string s_out = Neo::SmartContract::Contract::API_CreateSignatureRedeemScript(sin);
   std::cout << "PRINT s='" << s_out << "'" << std::endl;
   return s_out.c_str();
}



//
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

// ================================
//

vbyte
cpp_Util_GenerateVectorByte(int vsize, unsigned char initValue)
{
   vbyte v(vsize, initValue);
   return v;
}

// ------------

vbyte
cpp_Contract_CreateSignatureRedeemScript(vbyte pubkey)
{
   std::cout << pubkey.size() << std::endl;
   for (unsigned i = 0; i < pubkey.size(); i++)
      std::cout << (unsigned)pubkey[i] << std::endl;
   //
   // call method from Core! (see class Neo SmartContract Contract, method CreateSignatureRedeemScript)
   vbyte v(5); // 5 elements
   for (unsigned i = 0; i < v.size(); i++)
      v[i] = i;
   return v;
}

vbyte
cpp_Contract_CreateSignatureRedeemScript_Fake(vbyte pubkey)
{
   std::cout << pubkey.size() << std::endl;
   for (unsigned i = 0; i < pubkey.size(); i++)
      std::cout << (unsigned)pubkey[i] << std::endl;
   //
   // call method from Core! (see class Neo SmartContract Contract, method CreateSignatureRedeemScript)
   vbyte v(5); // 5 elements
   for (unsigned i = 0; i < v.size(); i++)
      v[i] = i;
   return v;
}

struct ECPointXYtest
{
   vbyte x;
   vbyte y;
   std::map<bool, int> toMap()
   {
      // bool: first (false-0) or second (true-1)
      std::map<bool, int> m;
      m[0] = 40;
      m[1] = 80;
      return m;
   }

   std::map<bool, vbyte> toMap2()
   {
      // bool: first (false-0) or second (true-1)
      std::map<bool, vbyte> m;
      m[0] = x;
      m[1] = y;
      return m;
   }
};

std::map<bool, int>
cpp_gen_xy()
{
   ECPointXYtest xy;
   xy.x = vbyte(5, -1);
   xy.y = vbyte(5, -2);
   return xy.toMap();
}

std::map<bool, vbyte>
cpp_gen_xy2()
{
   ECPointXYtest xy;
   xy.x = vbyte(5, -1);
   xy.y = vbyte(5, 10);
   return xy.toMap2();
}

vbyte
cpp_Contract_CreateSignatureRedeemScript_XY(std::map<bool, int> point)
{
   std::cout << "complex point: " << point[0] << " " << point[1] << std::endl;
   vbyte v(5); // return 5 elements
   for (unsigned i = 0; i < v.size(); i++)
      v[i] = i;
   return v; // return 5 elements
}

vbyte
cpp_Contract_CreateSignatureRedeemScript_XY2(std::map<bool, vbyte> point)
{
   std::cout << "complex point: " << point[0].size() << " " << point[1].size() << std::endl;
   std::cout << "complex point first element of each: " << (unsigned)point[0][0] << " " << (unsigned)point[1][0] << std::endl;
   vbyte v(5); // return 5 elements
   for (unsigned i = 0; i < v.size(); i++)
      v[i] = i;
   return v; // return 5 elements
}

// ================================


std::string
cpp_SmartContract_Contract_CreateSignatureRedeemScript(std::string s)
{
   return Neo::SmartContract::Contract::API_CreateSignatureRedeemScript(s);
}




EMSCRIPTEN_KEEPALIVE
extern "C"
int fib2(int n) {
  int i, t, a = 0, b = 1;
  for (i = 0; i < n; i++) {
    t = a + b;
    a = b;
    b = t;
  }
  return b;
}



/*
// these methods are provided to the external world (for nodejs, for example)
EMSCRIPTEN_BINDINGS(my_module)
{
   //emscripten::register_vector<unsigned char>("vector<unsigned char>");
   //emscripten::register_map<bool, int>("map<bool, int>");
   //emscripten::register_map<bool, vbyte>("map<int, vector<unsigned char>>");
   //emscripten::register_map<std::string, vbyte>("map<string, vector<unsigned char>>");

   //emscripten::function("my_cpp_teststr", &my_cpp_teststr);

   //emscripten::function("cpp_bignum_add", &cpp_bignum_add);

   //emscripten::function("cpp_Util_GenerateVectorByte", &cpp_Util_GenerateVectorByte);

   //emscripten::function("cpp_Contract_CreateSignatureRedeemScript_Fake", &cpp_Contract_CreateSignatureRedeemScript_Fake);
   //emscripten::function("cpp_Contract_CreateSignatureRedeemScript_XY", &cpp_Contract_CreateSignatureRedeemScript_XY);
   //emscripten::function("cpp_gen_xy", &cpp_gen_xy);
   //emscripten::function("cpp_Contract_CreateSignatureRedeemScript_XY2", &cpp_Contract_CreateSignatureRedeemScript_XY2);
   //emscripten::function("cpp_gen_xy2", &cpp_gen_xy2);
   //
   // ECPoint.jsapi.hpp
   // jsapi_ECPoint new_ECPoint(vbyte X, vbyte Y)
   //emscripten::function("cpp_ECPoint_new_ECPoint", &neo3_cpp_jsapi::cpp_ECPoint_new_ECPoint);
   //
   //emscripten::function("cpp_ECPoint_ToString", &neo3_cpp_jsapi::cpp_ECPoint_ToString);

   //
   // Contract.jsapi.hpp
   // vbyte cpp_Contract_CreateSignatureRedeemScript(jsapi_ECPoint point)
   //emscripten::function("cpp_SmartContract_Contract_CreateSignatureRedeemScript", &Neo::SmartContract::Contract::API_CreateSignatureRedeemScript);
}
*/