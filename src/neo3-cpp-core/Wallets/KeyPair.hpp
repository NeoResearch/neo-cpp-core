#pragma once

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

#include <neo3-cpp-core/SmartContract/scHelper.hpp>
//#include "./wHelper.hpp"

/*
using Neo.Cryptography;
using Neo.SmartContract;
using System;
using System.Text;
using static Neo.Wallets.Helper;
*/

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
      std::cout << "WARNING: always using 32 byte private key" << std::endl;
      vbyte pubKey(64, 0);
      external_get_pubkey_from_privkey(privateKey.data(), privateKey.size(), false, pubKey.data(), pubKey.size());

      vbyte vx(pubKey.begin(), pubKey.begin() + 32);
      vbyte vy(pubKey.begin() + 33, pubKey.begin() + 64);

      ECFieldElement X{ BigInteger{ vx }, *ECCurve::Secp256r1 };
      ECFieldElement Y{ BigInteger{ vy }, *ECCurve::Secp256r1 };

      ECPoint ecp{ X, Y, *ECCurve::Secp256r1 };

      /*
      std::cout << "getting EC Point: " << privateKey.size() << std::endl;
      //if (privateKey.Length != 32 && privateKey.Length != 96 && privateKey.Length != 104)
      //   throw new ArgumentException();
      //this.PrivateKey = privateKey[^32..];

      if (privateKey.size() == 32) {
        return Cryptography::ECC::ECCurve::Secp256r1.G * privateKey;
      } else {
      return Cryptography::ECC::ECPoint::FromBytes(privateKey, Cryptography::ECC::ECCurve::Secp256r1);
      }
      */

      return ecp;
   }

public:
   /*
        public KeyPair(byte[] privateKey)
        {
            if (privateKey.Length != 32 && privateKey.Length != 96 && privateKey.Length != 104)
                throw new ArgumentException();
            this.PrivateKey = privateKey[^32..];
            if (privateKey.Length == 32)
            {
                this.PublicKey = Cryptography.ECC.ECCurve.Secp256r1.G * privateKey;
            }
            else
            {
                this.PublicKey = Cryptography.ECC.ECPoint.FromBytes(privateKey, Cryptography.ECC.ECCurve.Secp256r1);
            }
        }
   */
   KeyPair(vbyte privateKey)
     : PublicKey(getECPoint(privateKey))
   {
   }

   KeyPair(const KeyPair& key)
     : PrivateKey{ key.PrivateKey }
     , PublicKey{ key.PublicKey }
   {
   }

   virtual ~KeyPair()
   {
   }

   /*
        public bool Equals(KeyPair other)
        {
            if (ReferenceEquals(this, other)) return true;
            if (other is null) return false;
            return PublicKey.Equals(other.PublicKey);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as KeyPair);
        }
*/
public:
   string Export() const
   {
      vbyte data(34, 0);
      data[0] = 0x80;
      //PrivateKey.CopyTo(data[1..]);
      std::copy(PrivateKey.begin(), PrivateKey.end(), data.begin() + 1);
      data[33] = 0x01;
      string wif = Neo::Cryptography::Base58::Base58CheckEncode(data);
      //data.Clear();
      return wif;
   }

public:
   string Export(string passphrase, int N = 16384, int r = 8, int p = 8) const
   {
      std::cout << "EXPORT NOT IMPLEMENTED IN KeyPair" << std::endl;
      /*
            UInt160 script_hash = Contract.CreateSignatureRedeemScript(PublicKey).ToScriptHash();
            string address = script_hash.ToAddress();
            byte[] addresshash = Encoding.ASCII.GetBytes(address).Sha256().Sha256()[..4];
            byte[] derivedkey = SCrypt.DeriveKey(Encoding.UTF8.GetBytes(passphrase), addresshash, N, r, p, 64);
            byte[] derivedhalf1 = derivedkey[..32];
            byte[] derivedhalf2 = derivedkey[32..];
            byte[] encryptedkey = XOR(PrivateKey, derivedhalf1).AES256Encrypt(derivedhalf2);
            Span<byte> buffer = stackalloc byte[39];
            buffer[0] = 0x01;
            buffer[1] = 0x42;
            buffer[2] = 0xe0;
            addresshash.CopyTo(buffer[3..]);
            encryptedkey.CopyTo(buffer[7..]);
            return Base58.Base58CheckEncode(buffer);
            */
      return "";
   }
   /*
        public override int GetHashCode()
        {
            return PublicKey.GetHashCode();
        }

        public override string ToString()
        {
            return PublicKey.ToString();
        }
    }
}
*/

public:
}; // class KeyPair
//
} // namespace Wallets
//
} // namespace Neo
  //
