#pragma once

#include<memory> // unique_ptr

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
class ECCurve
{
public:
   const BigInteger Q;
   const BigInteger A; // ECFieldElement
   const BigInteger B; // ECFieldElement
   const BigInteger N;

public:
   //const ECPoint<>& Infinity;

public:
   const std::unique_ptr<ECPoint> G; // TODO: make ECPoint and put Decode Point on ECCurveList

public:
   //const int ExpectedECPointLength;

public:
   ECCurve(BigInteger Q, const BigInteger A, const BigInteger B, BigInteger N, vbyte G);

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
#include"ECPoint.hpp"
//

Neo::Cryptography::ECC::ECCurve::ECCurve(BigInteger Q, const BigInteger A, const BigInteger B, BigInteger N, vbyte G) //const ECPoint<>& G)
     : Q{ Q }
     , A{ A }
     , B{ B }
     , N{ N }
     //, Infinity{ Infinity }
     //, G{ G }
     , G{ std::unique_ptr<ECPoint>{ new ECPoint{ECPoint::DecodePoint(G, *this) }} }
   {
      //this.Q = Q;
      //this.ExpectedECPointLength = (Q.GetBitLength() + 7) / 8;
      //this.A = new ECFieldElement(A, this);
      //this.B = new ECFieldElement(B, this);
      //this.N = N;
      //this.Infinity = new ECPoint(null, null, this);
      //this.G = ECPoint.DecodePoint(G, this);
   }
