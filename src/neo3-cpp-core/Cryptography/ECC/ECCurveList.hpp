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
   static ECCurve* secp256r1_ptr;
   static ECCurve* secp256k1_ptr;
   //
   static vbyte
   HexToBytes(const std::string& hex)
   {
      // TODO: implement (begin 0x)
      //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      vbyte bytes(hex.length() / 2);

      for (uint i = 0; i < hex.length(); i += 2) {
         std::string byteString = hex.substr(i, 2);
         neopt::byte b = (neopt::byte)strtol(byteString.c_str(), NULL, 16);
         bytes[i / 2] = b;
      }
      return bytes;
   }
   //
   static const ECCurve& Secp256r1()
   {
      if (!secp256r1_ptr) {
         std::stringstream ss;
         ss << "04"
            << "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
            << "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5";
         //
         //("04" + "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296" + "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5").HexToBytes()
         //
         secp256r1_ptr = new ECCurve{
            BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", 16 },
            BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC", 16 },
            BigInteger{ "005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B", 16 },
            BigInteger{ "00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551", 16 },
            HexToBytes(ss.str())
         };
      }

      return *secp256r1_ptr;
   };

   static const ECCurve& Secp256k1()
   {
      /*
      if (!secp256r1_ptr)
         secp256r1_ptr = new ECCurve{
            BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF" },
            BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC" },
            BigInteger{ "005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B" },
            BigInteger{ "00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551" },
            vbyte{} // empty G
         };*/

      return *secp256k1_ptr;
   };

}; // class ECCurveList
ECCurve* ECCurveList::secp256r1_ptr = nullptr;
ECCurve* ECCurveList::secp256k1_ptr = nullptr;
//
} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo
