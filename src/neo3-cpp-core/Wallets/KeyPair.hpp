#pragma once

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

#include <neo3-cpp-core/SmartContract/scHelper.hpp>
//#include "./wHelper.hpp"

namespace Neo {
//
namespace Wallets {
//
class KeyPair
{
public:
   vbyte PrivateKey;

public:
   Cryptography::ECC::ECPoint PublicKey;

public:
   UInt160 PublicKeyHash()
   {
      return Neo::SmartContract::scHelper::ToScriptHash(PublicKey.EncodePoint(true));
   }

private:
   static ECPoint getECPoint(vbyte privateKey)
   {
      //if (privateKey.Length != 32 && privateKey.Length != 96 && privateKey.Length != 104)
      //   throw new ArgumentException();
      //this.PrivateKey = privateKey[^32..];

      //if (privateKey.size() == 32) {
      //  return Cryptography::ECC::ECCurve.Secp256r1.G * privateKey;
      //} else {

      return Cryptography::ECC::ECPoint::FromBytes(privateKey, Cryptography::ECC::ECCurve::Secp256r1);
      //}
   }

public:
   KeyPair(vbyte privateKey)
     : PublicKey(getECPoint(PrivateKey))
   {
   }

public:
}; // class KeyPair
//
} // namespace Wallet
//
} // namespace Neo
  //
