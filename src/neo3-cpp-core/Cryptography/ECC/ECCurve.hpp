#pragma once

//using System.Globalization;
//using System.Numerics;

#include <csbiginteger-cpp/src/csBigIntegerLibClass.hpp>
using BigInteger = csbigintegerlib::BigInteger;

namespace Neo {
namespace Cryptography {
namespace ECC {
//
template<class unused = nullptr_t>
class ECPoint; // forward declaration
//
template<class unused = nullptr_t>
class ECFieldElement; // forward declaration
//
template<class unused = nullptr_t>
class ECCurve
{
public:
   const BigInteger Q;
   const ECFieldElement<>& A;
   const ECFieldElement<>& B;
   const BigInteger N;

public:
   const ECPoint<>& Infinity;

public:
   const ECPoint<>& G;

public:
   //const int ExpectedECPointLength;

private:
   /*
   ECCurve(BigInteger Q, BigInteger A, BigInteger B, BigInteger N, byte[] G) :
      Q{Q}, A{ECFieldElement<>{A, *this}}, B{ECFieldElement<>{B, *this}}, N{N}, Infinity{Infinity}, G{ECPoint::DecodePoint(G, *this)}
   {
      //this.Q = Q;
      //this.ExpectedECPointLength = (Q.GetBitLength() + 7) / 8;
      //this.A = new ECFieldElement(A, this);
      //this.B = new ECFieldElement(B, this);
      //this.N = N;
      //this.Infinity = new ECPoint(null, null, this);
      //this.G = ECPoint.DecodePoint(G, this);
   }
*/
   ECCurve(BigInteger Q, const ECFieldElement<>& A, const ECFieldElement<>& B, BigInteger N, const ECPoint<>& G)
     : Q{ Q }
     , A{ A }
     , B{ B }
     , N{ N }
     , Infinity{ Infinity }
     , G{ G }
   {
      //this.Q = Q;
      //this.ExpectedECPointLength = (Q.GetBitLength() + 7) / 8;
      //this.A = new ECFieldElement(A, this);
      //this.B = new ECFieldElement(B, this);
      //this.N = N;
      //this.Infinity = new ECPoint(null, null, this);
      //this.G = ECPoint.DecodePoint(G, this);
   }

public:
   /*
   static const ECCurve Secp256k1{
      
     BigInteger.Parse("00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F", NumberStyles.AllowHexSpecifier),
     BigInteger.Zero,
     7,
     BigInteger.Parse("00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141", NumberStyles.AllowHexSpecifier),
     ("04" + "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798" + "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8").HexToBytes()
     
   };
   */

public:
   /*
   static readonly ECCurve Secp256r1{
     BigInteger{"00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF"},
     BigInteger{"00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC"},
     BigInteger{"005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B"},
     BigInteger{"00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551"},
     vbyte{} // empty G
     //("04" + "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296" + "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5").HexToBytes()
      */
   /*
     BigInteger.Parse("00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", NumberStyles.AllowHexSpecifier),
     BigInteger.Parse("00FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC", NumberStyles.AllowHexSpecifier),
     BigInteger.Parse("005AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B", NumberStyles.AllowHexSpecifier),
     BigInteger.Parse("00FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551", NumberStyles.AllowHexSpecifier),
     ("04" + "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296" + "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5").HexToBytes()
     */
   //};

public:
   //static const ECCurve Secp256k1;

public:
   //static const ECCurve Secp256r1;

}; // class ECCurve
//
} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo
