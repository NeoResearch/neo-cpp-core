#pragma once

#ifndef NEO3_CRYPTOGRAPHY_ECC_ECC_HPP
#error Must include ECC before ECPoint
#endif

#include <neo3-cpp-core/neopt-common/System.hpp>
// JSON lib for external APIs
#include <neo3-cpp-core/neopt-common/json/jhelper.hpp>
//using Neo.IO;
//using System;
//using System.IO;
//using System.Numerics;
//using static Neo.Helper;
using neopt::IComparable;
using neopt::IEquatable;
using neopt::ISerializable;

#include "ECCurve.hpp"
//
#include "ECFieldElement.hpp" // hard dependency!!

namespace Neo {
//
namespace Cryptography {
//
namespace ECC {
//
//template<class unused>
//class ECCurve; // forward declaration
//
//template<class unused = nullptr_t>
//class ECFieldElement; // forward declaration
//
class ECPoint // TODO: inheritances........
//: IComparable<ECPoint>
//  , IEquatable<ECPoint>
//  , ISerializable
{

public:
   const ECFieldElement X, Y;
   //const ECCurve& Curve; // unused for now

public:
   bool IsInfinity()
   {
      //get { return X == null && Y == null; }
      return (X.Value.Length() == 0) && (Y.Value.Length() == 0);
   }

public:
   int Size() { return IsInfinity() ? 1 : 33; };

public:
   ECPoint(const ECCurve& curve)
     : X{ neopt::vbyte{}, curve }
     , Y{ neopt::vbyte{}, curve }
   //, Curve(curve)
   {}

   /*
   ECPoint()
     : this(null, null, ECCurve.Secp256r1)
   {}
   */

   //internal
   ECPoint(const ECFieldElement& x, const ECFieldElement& y, const ECCurve& curve)
     //ECPoint(vbyte x, vbyte y, ECCurve curve)
     : X(x)
     , Y(y)
   //, Curve(curve)
   {
      //if ((x is null ^ y is null) || (curve is null))
      //   throw new ArgumentException("Exactly one of the field elements is null");
      if ((x.Value.Length() == 0) && (y.Value.Length() == 0)) {
         std::cerr << "Exactly one of the field elements is null" << std::endl;
         assert(false);
      }
      //this->X = x;
      //this->Y = y;
   }
   /*
public
   int CompareTo(ECPoint other)
   {
      if (!Curve.Equals(other.Curve))
         throw new InvalidOperationException("Invalid comparision for points with different curves");
      if (ReferenceEquals(this, other))
         return 0;
      int result = X.CompareTo(other.X);
      if (result != 0)
         return result;
      return Y.CompareTo(other.Y);
   }

public
*/

   //static ECPoint DecodePoint(ReadOnlySpan<byte> encoded, ECCurve curve)
   static ECPoint DecodePoint(vbyte encoded, const ECCurve& curve)
   {
      //ECPoint p = null;
      ECPoint p{ ECFieldElement{ BigInteger::Zero, curve }, ECFieldElement{ BigInteger::Zero, curve }, curve };
      /*
      switch (encoded[0]) {
         case 0x02: // compressed
         case 0x03: // compressed
         {
            if (encoded.size() != (curve.ExpectedECPointLength + 1)) {
               //throw new FormatException("Incorrect length for compressed encoding");
               std::cerr << "ERROR: Incorrect length for compressed encoding" << std::endl;
               exit(1); // TODO: should avoid these breaking things!!! use optional...
            }
            int yTilde = encoded[0] & 1;
            BigInteger X1(vbyte{ encoded.begin() + 1, encoded.end() }, true, true);
            p = DecompressPoint(yTilde, X1, curve);
            break;
         }
         case 0x04: // uncompressed
         {
            if (encoded.Length != (2 * curve.ExpectedECPointLength + 1)) {
               //throw new FormatException("Incorrect length for uncompressed/hybrid encoding");
            }
            BigInteger X1(vbyte{ encoded.begin() + 1, encoded.begin() + (1 + curve.ExpectedECPointLength) }, true, true);
            BigInteger Y1(vbyte{ encoded.begin() + (1 + curve.ExpectedECPointLength), encoded.end() }, true, true);
            p = ECPoint{ ECFieldElement{ X1, curve }, ECFieldElement{ Y1, curve }, curve };
            break;
         }
         default: {
            //throw new FormatException("Invalid point encoding " + encoded[0]);
            std::cerr << "ERROR: Invalid point encoding " << encoded[0] << std::endl;
            exit(1); // TODO: avoid these breaks!! use optional...
         }
      };
      */
      std::cerr << "WARNING: Must use libcrypton to DecodePoint: bytearray -> ECPoint (x,y)!" << std::endl;
      return p;
   }

   /*

private
   static ECPoint DecompressPoint(int yTilde, BigInteger X1, ECCurve curve)
   {
      ECFieldElement x = new ECFieldElement(X1, curve);
      ECFieldElement alpha = x * (x.Square() + curve.A) + curve.B;
      ECFieldElement beta = alpha.Sqrt();

      //
      // if we can't find a sqrt we haven't got a point on the
      // curve - run!
      //
      if (beta == null)
         throw new ArithmeticException("Invalid point compression");

      BigInteger betaValue = beta.Value;
      int bit0 = betaValue.IsEven ? 0 : 1;

      if (bit0 != yTilde) {
         // Use the other root
         beta = new ECFieldElement(curve.Q - betaValue, curve);
      }

      return new ECPoint(x, beta, curve);
   }

   void ISerializable.Deserialize(BinaryReader reader)
   {
      ECPoint p = DeserializeFrom(reader, Curve);
      X = p.X;
      Y = p.Y;
   }

public
   static ECPoint DeserializeFrom(BinaryReader reader, ECCurve curve)
   {
      Span<byte> buffer = stackalloc byte[1 + curve.ExpectedECPointLength * 2];
      buffer[0] = reader.ReadByte();
      switch (buffer[0]) {
         case 0x02:
         case 0x03: {
            if (reader.Read(buffer[1..(1 + curve.ExpectedECPointLength)]) != curve.ExpectedECPointLength) {
               throw new FormatException();
            }
            return DecodePoint(buffer[..(1 + curve.ExpectedECPointLength)], curve);
         }
         case 0x04: {
            if (reader.Read(buffer[1..(1 + curve.ExpectedECPointLength * 2)]) != curve.ExpectedECPointLength * 2) {
               throw new FormatException();
            }
            return DecodePoint(buffer, curve);
         }
         default:
            throw new FormatException("Invalid point encoding " + buffer[0]);
      }
   }
*/

public:
   vbyte EncodePoint(bool commpressed)
   {
      if (IsInfinity())
         return vbyte(1, 0); // [0]
      vbyte data;
      if (commpressed) {
         data = vbyte(33, 0);
      } else {
         data = vbyte(65, 0);
         //byte[] yBytes = Y.Value.ToByteArray(isUnsigned : true, isBigEndian : true);
         vbyte yBytes = Y.Value.ToByteArray(true, true);
         neopt::Buffer::BlockCopy(yBytes, 0, data, 65 - yBytes.size(), yBytes.size());
      }
      //byte[] xBytes = X.Value.ToByteArray(isUnsigned : true, isBigEndian : true);
      vbyte xBytes = X.Value.ToByteArray(true, true);
      neopt::Buffer::BlockCopy(xBytes, 0, data, 33 - xBytes.size(), xBytes.size());
      //data[0] = commpressed ? Y.Value.IsEven ? (byte)0x02 : (byte)0x03 : (byte)0x04;
      data[0] = commpressed ? Y.Value.IsEven() ? (neopt::byte)0x02 : (neopt::byte)0x03 : (neopt::byte)0x04;
      return data;
   }

   /*
public
   bool Equals(ECPoint other)
   {
      if (ReferenceEquals(this, other))
         return true;
      if (ReferenceEquals(null, other))
         return false;
      if (IsInfinity && other.IsInfinity)
         return true;
      if (IsInfinity || other.IsInfinity)
         return false;
      return X.Equals(other.X) && Y.Equals(other.Y);
   }

public
   override bool Equals(object obj)
   {
      return Equals(obj as ECPoint);
   }
*/
public:
   static ECPoint FromBytes(vbyte pubkey, ECCurve curve)
   {
      switch (pubkey.size()) {
         case 33:
         case 65:
            return DecodePoint(pubkey, curve);
         case 64:
         case 72:
            return DecodePoint(pubkey, curve); // TODO
            //return DecodePoint(Concat(new byte[]{ 0x04 }, pubkey[^64..]), curve);
         case 96:
         case 104:
             return DecodePoint(pubkey, curve); // TODO
            //return DecodePoint(Concat(new byte[]{ 0x04 }, pubkey[^96.. ^ 32]), curve);
         default:
            NEOPT_EXCEPTION("Format Exception");
      }
   }

/*
public
   override int GetHashCode()
   {
      return X.GetHashCode() + Y.GetHashCode();
   }

   internal static ECPoint Multiply(ECPoint p, BigInteger k)
   {
      // floor(log2(k))
      int m = k.GetBitLength();

      // width of the Window NAF
      sbyte width;

      // Required length of precomputation array
      int reqPreCompLen;

      // Determine optimal width and corresponding length of precomputation
      // array based on literature values
      if (m < 13) {
         width = 2;
         reqPreCompLen = 1;
      } else if (m < 41) {
         width = 3;
         reqPreCompLen = 2;
      } else if (m < 121) {
         width = 4;
         reqPreCompLen = 4;
      } else if (m < 337) {
         width = 5;
         reqPreCompLen = 8;
      } else if (m < 897) {
         width = 6;
         reqPreCompLen = 16;
      } else if (m < 2305) {
         width = 7;
         reqPreCompLen = 32;
      } else {
         width = 8;
         reqPreCompLen = 127;
      }

      // The length of the precomputation array
      int preCompLen = 1;

      ECPoint[] preComp = new ECPoint[]{ p };
      ECPoint twiceP = p.Twice();

      if (preCompLen < reqPreCompLen) {
         // Precomputation array must be made bigger, copy existing preComp
         // array into the larger new preComp array
         ECPoint[] oldPreComp = preComp;
         preComp = new ECPoint[reqPreCompLen];
         Array.Copy(oldPreComp, 0, preComp, 0, preCompLen);

         for (int i = preCompLen; i < reqPreCompLen; i++) {
            // Compute the new ECPoints for the precomputation array.
            // The values 1, 3, 5, ..., 2^(width-1)-1 times p are
            // computed
            preComp[i] = twiceP + preComp[i - 1];
         }
      }

      // Compute the Window NAF of the desired width
      sbyte[] wnaf = WindowNaf(width, k);
      int l = wnaf.Length;

      // Apply the Window NAF to p using the precomputed ECPoint values.
      ECPoint q = p.Curve.Infinity;
      for (int i = l - 1; i >= 0; i--) {
         q = q.Twice();

         if (wnaf[i] != 0) {
            if (wnaf[i] > 0) {
               q += preComp[(wnaf[i] - 1) / 2];
            } else {
               // wnaf[i] < 0
               q -= preComp[(-wnaf[i] - 1) / 2];
            }
         }
      }

      return q;
   }

public
   static ECPoint Parse(string value, ECCurve curve)
   {
      return DecodePoint(value.HexToBytes(), curve);
   }

   void ISerializable.Serialize(BinaryWriter writer)
   {
      writer.Write(EncodePoint(true));
   }
*/
public:
   std::string ToString() //override
   {
      //return EncodePoint(true).ToHexString();
      return "TODO: ToString ECPoint";
   }
   /*
public
   static bool TryParse(string value, ECCurve curve, out ECPoint point)
   {
      try {
         point = Parse(value, curve);
         return true;
      } catch (FormatException) {
         point = null;
         return false;
      }
   }

   internal ECPoint Twice()
   {
      if (this.IsInfinity)
         return this;
      if (this.Y.Value.Sign == 0)
         return Curve.Infinity;
      ECFieldElement TWO = new ECFieldElement(2, Curve);
      ECFieldElement THREE = new ECFieldElement(3, Curve);
      ECFieldElement gamma = (this.X.Square() * THREE + Curve.A) / (Y * TWO);
      ECFieldElement x3 = gamma.Square() - this.X * TWO;
      ECFieldElement y3 = gamma * (this.X - x3) - this.Y;
      return new ECPoint(x3, y3, Curve);
   }

private
   static sbyte[] WindowNaf(sbyte width, BigInteger k)
   {
      sbyte[] wnaf = new sbyte[k.GetBitLength() + 1];
      short pow2wB = (short)(1 << width);
      int i = 0;
      int length = 0;
      while (k.Sign > 0) {
         if (!k.IsEven) {
            BigInteger remainder = k % pow2wB;
            if (remainder.TestBit(width - 1)) {
               wnaf[i] = (sbyte)(remainder - pow2wB);
            } else {
               wnaf[i] = (sbyte)remainder;
            }
            k -= wnaf[i];
            length = i;
         } else {
            wnaf[i] = 0;
         }
         k >>= 1;
         i++;
      }
      length++;
      sbyte[] wnafShort = new sbyte[length];
      Array.Copy(wnaf, 0, wnafShort, 0, length);
      return wnafShort;
   }

public
   static ECPoint operator-(ECPoint x)
   {
      return new ECPoint(x.X, -x.Y, x.Curve);
   }

public
   static ECPoint operator*(ECPoint p, byte[] n)
   {
      if (p == null || n == null)
         throw new ArgumentNullException();
      if (n.Length != 32)
         throw new ArgumentException();
      if (p.IsInfinity)
         return p;
      BigInteger k = new BigInteger(n, isUnsigned
                                    : true, isBigEndian
                                    : true);
      if (k.Sign == 0)
         return p.Curve.Infinity;
      return Multiply(p, k);
   }

public
   static ECPoint operator+(ECPoint x, ECPoint y)
   {
      if (x.IsInfinity)
         return y;
      if (y.IsInfinity)
         return x;
      if (x.X.Equals(y.X)) {
         if (x.Y.Equals(y.Y))
            return x.Twice();
         return x.Curve.Infinity;
      }
      ECFieldElement gamma = (y.Y - x.Y) / (y.X - x.X);
      ECFieldElement x3 = gamma.Square() - x.X - y.X;
      ECFieldElement y3 = gamma * (x.X - x3) - x.Y;
      return new ECPoint(x3, y3, x.Curve);
   }

public
   static ECPoint operator-(ECPoint x, ECPoint y)
   {
      if (y.IsInfinity)
         return x;
      return x + (-y);
   }
   */

   // ===================== EXPORT API METHODS =====================
   // these methods below provide service to APIs, like 'neopt-js'
   // --------------------------------------------------------------

public:
   // special method that encodes this as a json str (for external APIs)
   static std::string API_ToJsonStr(const ECPoint& ecpoint)
   {
      // X : "little-endian" hexstring
      // Y : "little-endian" hexstring

      std::stringstream ss;
      ss << "{";
      ss << "\"X\":"
         << "\"" << neopt::vhelper::ToHexString(ecpoint.X.Value.ToByteArray()) << "\""
         << ",";
      ss << "\"Y\":"
         << "\"" << neopt::vhelper::ToHexString(ecpoint.Y.Value.ToByteArray()) << "\""
         << ",";
      ss << "\"curve\":"
         << "\"secp256r1\""; // default curve
      ss << "}";
      return ss.str();
   }

   // special method that encodes this from a json str (for external APIs)
   static ECPoint API_FromJsonStr(std::string json)
   {
      neopt::uptr<neopt::JObject> jobj_p = neopt::jhelper::Parse(json);
      auto& jobj = *jobj_p;
      std::string x = jobj["X"]; // "little-endian" hexstring
      std::string y = jobj["Y"]; // "little-endian" hexstring
      //
      return ECPoint{
         ECFieldElement{ BigInteger{ x, 16 }, ECCurve::Secp256r1 },
         ECFieldElement{ BigInteger{ y, 16 }, ECCurve::Secp256r1 },
         ECCurve::Secp256r1
      };
   }
};
//
} // namespace ECC
//
} // namespace Cryptography
//
} // namespace Neo
