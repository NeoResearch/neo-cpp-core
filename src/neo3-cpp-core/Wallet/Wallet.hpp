#pragma once 

#include <neo3-cpp-core/Cryptography/Cryptography.hpp>
#include <neo3-cpp-core/ProtocolSettings.hpp>
#include "./WalletAccount.hpp"

namespace Neo {
//
namespace Wallets {
//
class Wallet
{
public:
 virtual WalletAccount CreateAccount(byte[] privateKey);


} // class Wallet
//
} // namespace Wallet
//
} // namespace Neo
  //

