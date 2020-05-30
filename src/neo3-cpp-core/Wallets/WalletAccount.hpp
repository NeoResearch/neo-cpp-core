#pragma once

#include <memory>
template<class X>
using uptr = std::unique_ptr<X>;

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

   uptr<Contract> pContract;

   std::string Address()
   {
      return wHelper::ToAddress(ScriptHash);
   }

   virtual bool HasKey() = 0;

   bool WatchOnly()
   {
      return this->pContract == nullptr;
   }

   virtual KeyPair GetKey() = 0;

protected:
   WalletAccount(const UInt160& scriptHash)
     : ScriptHash{ scriptHash }
   {
   }

}; // class WalletAccount
//
} // namespace Wallet
//
} // namespace Neo
  //
