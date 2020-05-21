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

// UGLY!!
#include <libcrypton/src/Crypto.h>

namespace Neo {
//
namespace SmartContract {
//
namespace cHelper {

static vbyte
Sha256(vbyte value)
{
   const libcrypton::ICrypto& ic = libcrypton::Crypto::Default();
   std::cout << "Running libcrypton" << std::endl;
   vbyte val = ic.Sha256(value);
   return val;
}

} // namespace cHelper
//
} // namespace SmartContract
//
} // namespace Neo
  //