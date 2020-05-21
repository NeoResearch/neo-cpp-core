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

namespace Neo {
//
namespace SmartContract {
//
namespace cHelper {

   static vbyte Sha256(vbyte value)
   {
      std::cout << "TODO: NOT IMPLEMENTED SHA256!" << std::endl;
      return value;
   }
   //vbyte Sha256(vbyte value, int offset, int count);

} // namespace cHelper
//
} // namespace SmartContract
//
} // namespace Neo
  //