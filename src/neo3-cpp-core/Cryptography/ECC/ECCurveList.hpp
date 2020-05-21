#pragma once

#include "ECCurve.hpp"
#include "ECPoint.hpp"

namespace Neo {
//
namespace Cryptography {
//
namespace ECC {
//
class ECCurveList
{
public:
   static ECCurve<>* secp256r1_ptr;
   //
   static const ECCurve<>& Secp256r1()
   {
      /*
      if (!secp256r1_ptr)
         secp256r1_ptr = new ECCurve<>{
            BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF" },
            BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC" },
            BigInteger{ "005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B" },
            BigInteger{ "00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551" },
            vbyte{} // empty G
         };*/

      return *secp256r1_ptr;
   };

}; // class ECCurveList
ECCurve<>* ECCurveList::secp256r1_ptr = nullptr;
//
} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo
