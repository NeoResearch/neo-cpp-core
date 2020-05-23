#pragma once

#include <map>
#include <vector>

#include <neo3-cpp-core/Cryptography/ECC/ECPoint.hpp>

namespace neo3_cpp_jsapi {

using jsapi_ECPoint = std::map<std::string, neopt::vbyte>;

// X -> "X" (vbyte instead of ECFieldElement)
// Y -> "Y" (vbyte instead of ECFieldElement)

jsapi_ECPoint
from_ECPoint(const ECPoint& p)
{
   // TODO
}

ECPoint
to_ECPoint(const jsapi_ECPoint& jsp)
{
   // TODO
}

} // namespace neo3_cpp_jsapi
