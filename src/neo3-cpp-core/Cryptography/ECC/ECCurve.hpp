#pragma once

#include <memory> // unique_ptr

//using System.Globalization;
//
//
//using System.Numerics;
#include <csbiginteger-cpp/src/csBigIntegerLibClass.hpp>
using BigInteger = csbigintegerlib::BigInteger;

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
   const ECFieldElement& A() { return *_A; }
   const ECFieldElement& B() { return *_B; }
   //
   const BigInteger N;

private:
   const std::unique_ptr<ECPoint> _Infinity; // cannot put on stack
public:
   const ECPoint& Infinity() { return *_Infinity; }

private:
   const std::unique_ptr<ECPoint> _G; // cannot put on stack, must 'heapify' it via unique_ptr
public:
   const ECPoint& G() { return *_G; }; // reference is good!

public:
   //const int ExpectedECPointLength;

public:
   ECCurve(BigInteger Q, BigInteger A, BigInteger B, BigInteger N, vbyte G);

public:
   // ================================================
   // PUBLIC CURVES ARE AVAILABLE ON 'ECCurveList.hpp'
   // ================================================
   //static const ECCurve Secp256k1;
   //static const ECCurve Secp256r1;

}; // class ECCurve
//
} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo
//
// forward declaration
#include "ECPoint.hpp"
//

Neo::Cryptography::ECC::ECCurve::ECCurve(BigInteger Q, BigInteger A, BigInteger B, BigInteger N, vbyte G) //const ECPoint<>& G)
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
