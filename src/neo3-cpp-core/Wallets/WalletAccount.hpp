#pragma once

#include <memory>

// using Neo.SmartContract;

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>
//
#include <neo3-cpp-core/SmartContract/Contract.hpp>
using Contract = Neo::SmartContract::Contract;

#include "./KeyPair.hpp"

#include "./wHelper.hpp"

namespace Neo {
//
namespace Wallets {
//
class WalletAccount
{
public:

   virtual ~WalletAccount()
   {
   }

   const UInt160 ScriptHash;
   std::string Label;
   bool IsDefault;
   bool Lock;

   neopt::uptr<Contract> pContract;

   std::string Address()
   {
      return wHelper::ToAddress(ScriptHash);
   }

   virtual bool HasKey() = 0;

   bool WatchOnly()
   {
      return this->pContract == nullptr;
   }

   virtual neopt::uptr<KeyPair> GetKey() = 0;

protected:
   WalletAccount(const UInt160& scriptHash)
     : ScriptHash{ scriptHash }
   {
   }

   // REMEMBER: pointer pContract is UNIQUE
   WalletAccount(const UInt160& scriptHash, Contract* pContract)
     : ScriptHash{ scriptHash }, pContract { neopt::uptr<Contract>{pContract} }
   {
   }

}; // class WalletAccount
//
} // namespace Wallets
//
} // namespace Neo
  //
