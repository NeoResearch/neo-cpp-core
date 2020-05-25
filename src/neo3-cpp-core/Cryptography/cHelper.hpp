#pragma once
// this may 'glue' to 'libcrypton' or any 'js' crypto library
#include <neo3-cpp-core/ExternalCrypto.h>

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