#pragma once

#include <map>
#include <vector>

#include <neo3-cpp-core/Cryptography/ECC/ECPoint.hpp>

namespace neo3_cpp_jsapi {

using jsapi_ECPoint = std::map<std::string, neopt::vbyte>;

// X -> "X" (vbyte representing ECFieldElement)
// Y -> "Y" (vbyte representing ECFieldElement)

jsapi_ECPoint
from_ECPoint(const ECPoint& p)
{
   jsapi_ECPoint xy;
   xy["X"] = p.X.Value.ToByteArray();
   xy["Y"] = p.X.Value.ToByteArray();
   return xy;
}

ECPoint
to_ECPoint(jsapi_ECPoint p)
{
   return ECPoint{
      ECFieldElement{ BigInteger{ p["X"] }, ECCurve::Secp256r1 },
      ECFieldElement{ BigInteger{ p["Y"] }, ECCurve::Secp256r1 },
      ECCurve::Secp256r1
   };
}

// ========== PUBLIC ===========

// defaults to curve secp256r1
jsapi_ECPoint
cpp_ECPoint_new_ECPoint(vbyte X, vbyte Y)
{
   return from_ECPoint(
     ECPoint{
       ECFieldElement{ BigInteger{ X }, ECCurve::Secp256r1 },
       ECFieldElement{ BigInteger{ Y }, ECCurve::Secp256r1 },
       ECCurve::Secp256r1 });
}

std::string
cpp_ECPoint_ToString(jsapi_ECPoint p)
{
   return to_ECPoint(p).ToString();
}

} // namespace neo3_cpp_jsapi
