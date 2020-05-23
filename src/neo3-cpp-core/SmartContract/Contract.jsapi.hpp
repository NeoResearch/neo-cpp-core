#pragma once

#include <neo3-cpp-core/SmartContract/Contract.hpp>
#include <neo3-cpp-core/Cryptography/ECC/ECPoint.jsapi.hpp>

namespace neo3_cpp_jsapi {



vbyte
cpp_Contract_CreateSignatureRedeemScript(jsapi_ECPoint point)
{
   std::cout << "complex point: " << point["X"].size() << " " << point["Y"].size() << std::endl;
   std::cout << "complex point first element of each: " << (unsigned)point["X"][0] << " " << (unsigned)point["Y"][0] << std::endl;
   vbyte v(5); // return 5 elements
   for (unsigned i = 0; i < v.size(); i++)
      v[i] = i;
   return v; // return 5 elements
}

} // namespace neo3_cpp_jsapi