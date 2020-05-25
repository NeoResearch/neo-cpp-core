#include "ExternalCrypto.h"

// using libcrypton to implement "ExternalCrypto"
#include <libcrypton/src/Crypto.h>

#include<iostream>

// perform sha256 on input and returns used size (in bytes). output must be pre-allocated.
extern "C" int
external_sha256(neopt::byte* input, int sz_input, neopt::byte* output, int sz_output)
{
   const libcrypton::ICrypto& ic = libcrypton::Crypto::Default();
   std::cout << "Running libcrypton" << std::endl;
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
   std::cout << "Running libcrypton" << std::endl;
   //
   neopt::vbyte value(input, input + sz_input);
   neopt::vbyte val = ic.RIPEMD160(value);
   std::copy(val.begin(), val.end(), output);
   // TODO: verify 'sz_output' for 'safer' operation
   return val.size();
}