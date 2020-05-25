#pragma once

#include <csbiginteger-cpp/src/csBigIntegerLibClass.hpp>
using BigInteger = csbigintegerlib::BigInteger;

//using System;
//using System.Linq;
//using System.Numerics;
//using System.Text;
//using static Neo.Helper;

//#ifdef CREATED_CHELPER
//#error Should include Base58 BEFORE than cHelper
//#endif

#include "cHelper.hpp"

namespace Neo {
//
namespace Cryptography {
//
//using namespace Neo::Cryptography::cHelper;
//
class Base58
{
public:
   inline static const std::string Alphabet{ "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz" };

public:
   static vbyte Base58CheckDecode(const std::string& input)
   {
      //if (input is null)
      //   throw new ArgumentNullException(nameof(input));
      vbyte buffer = Decode(input);
      if (buffer.size() < 4) {
         //throw new FormatException();
         NEOPT_EXCEPTION("Format Exception");
      }
      vbyte checksum = cHelper::Sha256(cHelper::Sha256(buffer, 0, buffer.size() - 4));
      // TODO: perform CHECKSUM
      /*
      if (!buffer.AsSpan(^4).SequenceEqual(checksum.AsSpan(..4)))
         throw new FormatException();
      var ret = buffer[..^ 4];
      Array.Clear(buffer, 0, buffer.Length);
      */
      vbyte ret(buffer.begin(), buffer.begin() + 4); // TODO: verify
      return ret;
   }

public:
   //static string Base58CheckEncode(this ReadOnlySpan<byte> data)
   static std::string Base58CheckEncode(const vbyte& data)
   {
      vbyte checksum = cHelper::Sha256(cHelper::Sha256(data));
      //Span<byte> buffer = stackalloc byte[data.Length + 4];
      vbyte buffer(data.size() + 4);
      //data.CopyTo(buffer);
      std::copy(data.begin(), data.end(), buffer.data());
      //
      //checksum.AsSpan(..4).CopyTo(buffer[data.Length..]);
      std::copy(checksum.begin(), checksum.begin() + 4, buffer.data() + data.size());
      //
      std::string ret = Encode(buffer);
      //buffer.Clear();
      return ret;
   }

public:
   //static byte[] Decode(string input)
   static vbyte Decode(const std::string& input)
   {
      // Decode Base58 string to BigInteger
      BigInteger bi = BigInteger::Zero;
      for (int i = 0; i < input.size(); i++) {
         //int digit = Alphabet.IndexOf(input[i]);
         string::size_type digit = Alphabet.find(input[i], 0);
         if (digit == string::npos) {
            //throw new FormatException($ "Invalid Base58 character '{input[i]}' at position {i}");
            NEOPT_EXCEPTION("Invalid Base58 Char");
         }
         bi = BigInteger{ bi * Alphabet.size() + digit };
      }

      // Encode BigInteger to byte[]
      // Leading zero bytes get encoded as leading `1` characters
      int leadingZeroCount = input.TakeWhile(c = > c == Alphabet[0]).Count();
      vbyte leadingZeros(leadingZeroCount, 0);
      if (bi.IsZero())
         return leadingZeros;
      vbyte bytesWithoutLeadingZeros = bi.ToByteArray(true, true);
      return neopt::vhelper::Concat(leadingZeros, bytesWithoutLeadingZeros);
   }

public:
   //static string Encode(ReadOnlySpan<byte> input)
   static std::string Encode(const vbyte& input)
   {
      // Decode byte[] to BigInteger
      BigInteger value(input, true, true);

      // Encode BigInteger to Base58 string
      StringBuilder sb; // = new StringBuilder();

      while (value > 0) {
         value = BigInteger.DivRem(value, Alphabet.size(), out var remainder);
         sb.Insert(0, Alphabet[(int)remainder]);
      }

      // Append `1` for each leading 0 byte
      for (int i = 0; i < input.Length && input[i] == 0; i++) {
         sb.Insert(0, Alphabet[0]);
      }
      return sb.ToString();
   }
}; // class Base58
//
} // namespace Cryptography
//
} // namespace Neo
