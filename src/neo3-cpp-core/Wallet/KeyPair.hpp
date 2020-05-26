#pragma once 

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

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
         UInt160 PublicKeyHash => PublicKey.EncodePoint(true).ToScriptHash();

        public:
        KeyPair(byte[] privateKey)
        {
            if (privateKey.Length != 32 && privateKey.Length != 96 && privateKey.Length != 104)
                throw new ArgumentException();
            this.PrivateKey = privateKey[^32..];
            if (privateKey.Length == 32)
            {
                this.PublicKey = Cryptography::ECC::ECCurve.Secp256r1.G * privateKey;
            }
            else
            {
                this.PublicKey = Cryptography::ECC::ECPoint.FromBytes(privateKey, Cryptography.ECC.ECCurve.Secp256r1);
            }
        }

} // class KeyPair
//
} // namespace Wallet
//
} // namespace Neo
  //

