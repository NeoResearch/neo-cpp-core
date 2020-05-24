#pragma once

#ifndef NEO3_CRYPTOGRAPHY_ECC_ECC_HPP
#error Must include ECC before ECCurve
#endif

#include <unique_ref/unique_ref.hpp>
using unique_ref::ucref; // 'uref' for 'concrete' types (safer!)
using unique_ref::uref;  // unique references from optframe project

//using System.Globalization;
//
//
//using System.Numerics;
#include <csbiginteger-cpp/src/csBigIntegerLibClass.hpp>
using BigInteger = csbigintegerlib::BigInteger;

#include <neo3-cpp-core/Helper.hpp> // Neo Helper

namespace Neo {
//
namespace Cryptography {
//
namespace ECC {
//
class ECPoint; // forward declaration
//
class ECFieldElement; // forward declaration
//
class ECCurve
{
public:
   const BigInteger Q;

public:
   const ucref<ECFieldElement> A;
   const ucref<ECFieldElement> B;
   //
   const BigInteger N;

public:
   const ucref<ECPoint> Infinity;

public:
   const ucref<ECPoint> G;

public:
   const int ExpectedECPointLength;

public:
   ECCurve(BigInteger Q, BigInteger A, BigInteger B, BigInteger N, vbyte G);

public:
   static const ucref<ECCurve> Secp256k1;
   static const ucref<ECCurve> Secp256r1;

}; // class ECCurve
//
} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo

// =========== FORWARD DECLARATIONS =============

// forward declaration
#include "ECPoint.hpp"
// forward declaration
#include "ECFieldElement.hpp"
//

// =========== BACK TO DEFINITIONS ===========

namespace Neo {
//
namespace Cryptography {
//
namespace ECC {
//
ECCurve::ECCurve(BigInteger Q, BigInteger A, BigInteger B, BigInteger N, vbyte G) //const ECPoint<>& G)
  : Q{ Q }
  , A{ ECFieldElement{ A, *this } }
  , B{ ECFieldElement{ B, *this } }
  , N{ N }
  , Infinity{ ECPoint{ *this } }
  , G{ ECPoint::DecodePoint(G, *this) }
  , ExpectedECPointLength{ (Helper::GetBitLength(Q) + 7) / 8 }
{
   //this.Q = Q;
   //this.ExpectedECPointLength = (Q.GetBitLength() + 7) / 8;
   //this.A = new ECFieldElement(A, this);
   //this.B = new ECFieldElement(B, this);
   //this.N = N;
   //this.Infinity = new ECPoint(null, null, this);
   //this.G = ECPoint.DecodePoint(G, this);
}

const ucref<ECCurve> ECCurve::Secp256r1{
   ECCurve{
      // using '0x' prefix, because csBigInteger.js requires this to interpret as BigEndian
      // for C++ and C#, it's not necessary, but not bad.
      // TODO: we must fix csBigInteger.js by defining string hex inputs always as bigendian
     BigInteger{ "0x00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", 16 },
     BigInteger{ "0x00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC", 16 },
     BigInteger{ "0x005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B", 16 },
     BigInteger{ "0x00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551", 16 },
     Helper::HexToBytes("046B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C2964FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5")
     //ss << "04"
     // << "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
     // << "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5";
   }
};

const ucref<ECCurve> ECCurve::Secp256k1{
   ECCurve{
     BigInteger{ "0x00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", 16 },
     BigInteger::Zero,
     BigInteger{ 7 },
     BigInteger{ "0x00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141", 16 },
     Helper::HexToBytes("0479BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8")
     //
     //("04" + "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798" + "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8").HexToBytes()
   }
};

} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo