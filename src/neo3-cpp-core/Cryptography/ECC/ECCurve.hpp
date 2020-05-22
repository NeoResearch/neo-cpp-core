#pragma once

#include <memory> // unique_ptr

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

private:
   const std::unique_ptr<ECFieldElement> _A; // cannot put A on stack
   const std::unique_ptr<ECFieldElement> _B; // cannot put A on stack

public:
   const ECFieldElement& A() const { return *_A; }
   const ECFieldElement& B() const { return *_B; }
   //
   const BigInteger N;

private:
   const std::unique_ptr<ECPoint> _Infinity; // cannot put on stack
public:
   const ECPoint& Infinity() const { return *_Infinity; }

private:
   const std::unique_ptr<ECPoint> _G; // cannot put on stack, must 'heapify' it via unique_ptr
public:
   const ECPoint& G() const { return *_G; }; // reference is good!

public:
   //const int ExpectedECPointLength;

public:
   ECCurve(BigInteger Q, BigInteger A, BigInteger B, BigInteger N, vbyte G);

public:
   // ================================================
   // PUBLIC CURVES ARE AVAILABLE ON 'ECCurveList.hpp'
   // ================================================
private:
   static const std::unique_ptr<ECCurve> _Secp256r1; // cannot put on stack
   static const std::unique_ptr<ECCurve> _Secp256k1; // cannot put on stack
public:
   static const ECCurve& Secp256k1() { return *_Secp256k1; };
   static const ECCurve& Secp256r1() { return *_Secp256r1; };

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
  , _A{ std::unique_ptr<ECFieldElement>{ new ECFieldElement{ A, *this } } }
  , _B{ std::unique_ptr<ECFieldElement>{ new ECFieldElement{ B, *this } } }
  , N{ N }
  , _Infinity{ std::unique_ptr<ECPoint>{ new ECPoint{ *this } } }
  , _G{ std::unique_ptr<ECPoint>{ new ECPoint{ ECPoint::DecodePoint(G, *this) } } }
{
   //this.Q = Q;
   //this.ExpectedECPointLength = (Q.GetBitLength() + 7) / 8;
   //this.A = new ECFieldElement(A, this);
   //this.B = new ECFieldElement(B, this);
   //this.N = N;
   //this.Infinity = new ECPoint(null, null, this);
   //this.G = ECPoint.DecodePoint(G, this);
}

const std::unique_ptr<ECCurve> ECCurve::_Secp256r1 =
  std::unique_ptr<ECCurve>{ new ECCurve{
    BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", 16 },
    BigInteger{ "00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC", 16 },
    BigInteger{ "005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B", 16 },
    BigInteger{ "00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551", 16 },
    Helper::HexToBytes("046B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C2964FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5")
    //ss << "04"
    // << "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"
    // << "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5";
  } };

const std::unique_ptr<ECCurve> ECCurve::_Secp256k1 =
  std::unique_ptr<ECCurve>{ new ECCurve{
    BigInteger{ "00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", 16 },
    BigInteger::Zero,
    BigInteger{ 7 },
    BigInteger{ "00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141", 16 },
    Helper::HexToBytes("0479BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8")
    //
    //("04" + "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798" + "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8").HexToBytes()
  } };

} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo