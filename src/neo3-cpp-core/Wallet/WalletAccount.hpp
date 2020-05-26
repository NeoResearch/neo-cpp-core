#pragma once 

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>

namespace Neo {
//
namespace Wallets {
//
class WalletAccount
{
        public:
         readonly UInt160 ScriptHash;

        protected:
         WalletAccount(UInt160 scriptHash)
        {
            this.ScriptHash = scriptHash;
        }

} // class Wallet
//
} // namespace Wallet
//
} // namespace Neo
  //

