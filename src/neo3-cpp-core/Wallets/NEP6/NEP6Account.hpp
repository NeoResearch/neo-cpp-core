#pragma once

#ifdef NEP6_WALLET
#error SHOULD INCLUDE NEP6Account before NEP6Wallet
#endif

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

#include "../WalletAccount.hpp"

namespace Neo {
//
namespace Wallets {
//
namespace NEP6 {
   //
      template<class X>
   using uptr = std::unique_ptr<X>;
//
class NEP6Wallet; // Forward Declaration
//
class NEP6Account : public WalletAccount
{

private:
   const NEP6Wallet& wallet;

private:
   string nep2key{ "" };

private:
   string nep2KeyNew{ "" }; //null;
private:
   uptr<KeyPair> key;

public:
   // JObject Extra;

public:
   bool Decrypted()
   {
      //return nep2key == null || key != null;
      return nep2key == "" || key != nullptr;
   }

public:
   bool HasKey() override
   {
      return nep2key != "";
   }

public:
   NEP6Account(const NEP6Wallet& wallet, UInt160 scriptHash, string nep2key = "", Contract* pContract = nullptr)
     : WalletAccount(scriptHash, pContract)
     , wallet{ wallet }
     , nep2key{ nep2key }
   {
   }

   virtual ~NEP6Account()
   {
   }

public:
   NEP6Account(const NEP6Wallet& wallet, const UInt160& scriptHash, KeyPair key, string password, Contract* pContract = nullptr);

   // FORWARD

   /*
        public:
         static NEP6Account FromJson(JObject json, const NEP6Wallet& wallet)
        {
            return new NEP6Account(wallet, json["address"].AsString().ToScriptHash(), json["key"]?.AsString())
            {
                Label = json["label"]?.AsString(),
                IsDefault = json["isDefault"].AsBoolean(),
                Lock = json["lock"].AsBoolean(),
                Contract = NEP6Contract.FromJson(json["contract"]),
                Extra = json["extra"]
            };
        }
        */

   //override KeyPair GetKey()
public:
   uptr<KeyPair> GetKey() override;
   // Forward declaration

public:
   uptr<KeyPair> GetKey(string password);
   // forward declaration

   /*
        public:
         JObject ToJson()
        {
            JObject account = new JObject();
            account["address"] = ScriptHash.ToAddress();
            account["label"] = Label;
            account["isDefault"] = IsDefault;
            account["lock"] = Lock;
            account["key"] = nep2key;
            account["contract"] = ((NEP6Contract)Contract)?.ToJson();
            account["extra"] = Extra;
            return account;
        }
*/
public:
   bool VerifyPassword(string password);
   /*
        /// <summary>
        /// Cache draft nep2key during wallet password changing process. Should not be called alone for a single account
        /// </summary>
        internal:
         bool ChangePasswordPrepare(string password_old, string password_new)
        {
            if (WatchOnly) return true;
            KeyPair keyTemplate = key;
            if (nep2key == null)
            {
                if (keyTemplate == null)
                {
                    return true;
                }
            }
            else
            {
                try
                {
                    keyTemplate = new KeyPair(Wallet.GetPrivateKeyFromNEP2(nep2key, password_old, wallet.Scrypt.N, wallet.Scrypt.R, wallet.Scrypt.P));
                }
                catch
                {
                    return false;
                }
            }
            nep2KeyNew = keyTemplate.Export(password_new, wallet.Scrypt.N, wallet.Scrypt.R, wallet.Scrypt.P);
            return true;
        }

        private:
         void ChangePasswordCommit()
        {
            if (nep2KeyNew != null)
            {
                nep2key = Interlocked.Exchange(ref nep2KeyNew, null);
            }
        }

        private:
         void ChangePasswordRoolback()
        {
            nep2KeyNew = null;
        }
        */

}; // class NEP6Account
//
} // namespace NEP6
//
} // namespace Wallets
//
} // namespace Neo
  //

// Forward declaration
#include "NEP6Wallet.hpp"

namespace Neo {
//
namespace Wallets {
//
namespace NEP6 {

NEP6Account::NEP6Account(const NEP6Wallet& wallet, const UInt160& scriptHash, KeyPair key, string password, Contract* pContract)
  : NEP6Account(wallet, scriptHash, key.Export(password, wallet.Scrypt.N, wallet.Scrypt.R, wallet.Scrypt.P), pContract)
{
   this->key = uptr<KeyPair>{ new KeyPair(key) };
}

uptr<KeyPair>
NEP6Account::GetKey()
{
   if (nep2key == "null")
      return nullptr;
   if (key == nullptr) {
      key = wallet.DecryptKey(nep2key);
   }
   return uptr<KeyPair>{ new KeyPair(*key) };
}

bool
NEP6Account::VerifyPassword(string password)
{
   //try {
   std::optional<vbyte> vout = Wallet::GetPrivateKeyFromNEP2(nep2key, password, wallet.Scrypt.N, wallet.Scrypt.R, wallet.Scrypt.P);

   if (vout)
      return true;
   //} catch (FormatException) {
   else
      return false;
   //}
}

uptr<KeyPair>
NEP6Account::GetKey(string password)
{
   if (nep2key == "")
      return nullptr;
   //
   if (key == nullptr) {
      // TODO: check return from 'GetPrivateKeyFromNEP2'
      KeyPair* newKey = new KeyPair(*Wallet::GetPrivateKeyFromNEP2(nep2key, password, wallet.Scrypt.N, wallet.Scrypt.R, wallet.Scrypt.P));
      key = uptr<KeyPair>{ newKey };
   }
   //
   return uptr<KeyPair>{ new KeyPair(*key) };
}

} // namespace NEP6
//
} // namespace Wallets
//
} // namespace Neo
  //
