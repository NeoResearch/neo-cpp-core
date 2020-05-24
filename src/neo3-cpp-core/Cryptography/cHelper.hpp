#pragma once

#include <neo3-cpp-core/Cryptography/ECC/ECPoint.hpp>
using namespace Neo::Cryptography::ECC;
#include <neo3-cpp-vm/ScriptBuilder.hpp>
using namespace Neo::VM;
//using Neo.Wallets;
//using System;
//using System.Linq;
//
#include <neo3-cpp-core/SmartContract/InteropService.Crypto.hpp>

// this may 'glue' to 'libcrypton' or any 'js' crypto library
#include <neo3-cpp-core/ExternalCrypto.h>

namespace Neo {
//
namespace SmartContract {
//
namespace cHelper {

static vbyte
Sha256(vbyte input)
{
   vbyte vout(32, 0);
   external_sha256(input.data(), input.size(), vout.data(), vout.size());
   // TODO: verify 'used' bytes
   return vout;
}

} // namespace cHelper
//
} // namespace SmartContract
//
} // namespace Neo
  //