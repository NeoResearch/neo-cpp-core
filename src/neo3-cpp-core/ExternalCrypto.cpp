#include "ExternalCrypto.h"

// using libcrypton to implement "ExternalCrypto"
#include <libcrypton/src/Crypto.h>

#include <iostream>

// perform sha256 on input and returns used size (in bytes). output must be pre-allocated.
extern "C" int
external_sha256(neopt::byte* input, int sz_input, neopt::byte* output, int sz_output)
{
   const libcrypton::ICrypto& ic = libcrypton::Crypto::Default();
   //std::cout << "Running libcrypton" << std::endl;
   //
   neopt::vbyte value(input, input + sz_input);
   neopt::vbyte val = ic.Sha256(value);
   std::copy(val.begin(), val.end(), output);
   // TODO: verify 'sz_output' for 'safer' operation
   return val.size();
}

// perform ripemd160 on input and returns used size (in bytes). output must be pre-allocated.
extern "C" int
external_ripemd160(neopt::byte* input, int sz_input, neopt::byte* output, int sz_output)
{
   const libcrypton::ICrypto& ic = libcrypton::Crypto::Default();
   //std::cout << "Running libcrypton" << std::endl;
   //
   neopt::vbyte value(input, input + sz_input);
   neopt::vbyte val = ic.RIPEMD160(value);
   std::copy(val.begin(), val.end(), output);
   // TODO: verify 'sz_output' for 'safer' operation
   return val.size();
}

extern "C" int
external_rand(int byte_count, neopt::byte* output, int sz_output)
{
   // TODO: verify if it's better to keep const or not... entropy is actually lost on practice!
   // anyway, maybe it's just enough to put method RandBytes as 'const'
   libcrypton::ICrypto& ic = const_cast<libcrypton::ICrypto&>(libcrypton::Crypto::Default());
   //std::cout << "Running libcrypton" << std::endl;
   //
   if (byte_count >= 1024 * 10) // 10 KiB maximum (preserve entropy)
      return 0;
   libcrypton::SecureBytes val = ic.RandBytes(byte_count);
   std::copy(val.data(), val.data() + val.size(), output);
   // TODO: verify 'sz_output' for 'safer' operation
   return val.size();
}

// call Crypto to generate ('compressed')
extern "C" int
external_get_pubkey_from_privkey(neopt::byte* input, int sz_input, bool compressed, neopt::byte* output, int sz_output)
{
   libcrypton::ICrypto& ic = const_cast<libcrypton::ICrypto&>(libcrypton::Crypto::Default());
   //std::cout << "Running libcrypton" << std::endl;
   //
   libcrypton::SecureBytes vinput(input, input + sz_input);
   neopt::vbyte val = ic.GetPublicKeyFromPrivateKey(vinput, compressed);
   //
   std::copy(val.data(), val.data() + val.size(), output);
   // TODO: verify 'sz_output' for 'safer' operation
   return val.size();
}