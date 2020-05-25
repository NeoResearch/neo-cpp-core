#pragma once
// this may 'glue' to 'libcrypton' or any 'js' crypto library
#include <neo3-cpp-core/ExternalCrypto.h>

//#include "Base58.hpp"

#define CREATED_CHELPER

namespace Neo {
//
namespace Cryptography {
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

static vbyte
Sha256(const vbyte& value, int offset, int count)
{
   vbyte val(value.begin() + offset, value.begin() + offset + count);
   return Sha256(val);
}

static vbyte
RIPEMD160(vbyte input)
{
   vbyte vout(20, 0);
   external_ripemd160(input.data(), input.size(), vout.data(), vout.size());
   // TODO: verify 'used' bytes
   return vout;
}

} // namespace cHelper
//
} // namespace SmartContract
//
} // namespace Neo
  //