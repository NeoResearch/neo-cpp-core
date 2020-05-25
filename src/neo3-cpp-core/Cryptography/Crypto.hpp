#pragma once

//using System;
//using System.Numerics;
//using System.Security.Cryptography;

// TODO: add Base58 here!
//#include "Base58.hpp"
//
#include "cHelper.hpp"
#include <neo3-cpp-core/ExternalCrypto.h>

namespace Neo {
//
namespace Cryptography {
//
namespace Crypto {

using namespace Neo::Cryptography::cHelper;

static vbyte
Hash160(const vbyte& message)
{
   return RIPEMD160(Sha256(message));
}

static vbyte
Hash256(const vbyte& message)
{
   return Sha256(Sha256(message));
}

/*
static byte[] Sign(byte[] message, byte[] prikey, byte[] pubkey)
{
   using(var ecdsa = ECDsa.Create(new ECParameters{
           Curve = ECCurve.NamedCurves.nistP256,
           D = prikey,
           Q = new ECPoint{
             X = pubkey[..32],
             Y = pubkey[32..] } }))
   {
      return ecdsa.SignData(message, HashAlgorithmName.SHA256);
   }
}


static bool
VerifySignature(ReadOnlySpan<byte> message, ReadOnlySpan<byte> signature, ECC.ECPoint pubkey)
{
   if (pubkey.Curve == ECC.ECCurve.Secp256r1) {
      byte[] buffer = pubkey.EncodePoint(false);
      using(var ecdsa = ECDsa.Create(new ECParameters{
              Curve = ECCurve.NamedCurves.nistP256,
              Q = new ECPoint{
                X = buffer[1..33],
                Y = buffer[33..] } }))
      {
         return ecdsa.VerifyData(message, signature, HashAlgorithmName.SHA256);
      }
   } else {
      var ecdsa = new ECC.ECDsa(pubkey);
      var r = new BigInteger(signature[..32], true, true);
      var s = new BigInteger(signature[32..], true, true);
      return ecdsa.VerifySignature(message.Sha256(), r, s);
   }
}


static bool
VerifySignature(ReadOnlySpan<byte> message, ReadOnlySpan<byte> signature, ReadOnlySpan<byte> pubkey, ECC.ECCurve curve)
{
   if (curve == ECC.ECCurve.Secp256r1) {
      if (pubkey.Length == 33 && (pubkey[0] == 0x02 || pubkey[0] == 0x03)) {
         try {
            pubkey = ECC.ECPoint.DecodePoint(pubkey, curve).EncodePoint(false).AsSpan(1);
         } catch {
            return false;
         }
      } else if (pubkey.Length == 65 && pubkey[0] == 0x04) {
         pubkey = pubkey[1..];
      } else {
         throw new ArgumentException();
      }
      using(var ecdsa = ECDsa.Create(new ECParameters{
              Curve = ECCurve.NamedCurves.nistP256,
              Q = new ECPoint{
                X = pubkey[..32].ToArray(),
                Y = pubkey[32..].ToArray() } }))
      {
         return ecdsa.VerifyData(message, signature, HashAlgorithmName.SHA256);
      }
   } else {
      var ecdsa = new ECC.ECDsa(ECC.ECPoint.DecodePoint(pubkey, curve));
      var r = new BigInteger(signature[..32], true, true);
      var s = new BigInteger(signature[32..], true, true);
      return ecdsa.VerifySignature(message.Sha256(), r, s);
   }
*/
//
} // namespace Crypto
//
} // namespace Cryptography
//
} // namespace Neo
