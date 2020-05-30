//
// building lib-neopt-core in javascript (via emscripten)
//
#include <emscripten.h>
//
// for helper prints and strings
#include <iostream>

// =======================================================================================
// these are C++ methods provided to emscripten (js part) via connection on C++ Neo3 Core
//
#include <neo3-cpp-core/Core.hpp>
//
// these are the specs for lib-neopt-core
//
#include <lib-neopt-core/lib-neopt-core.h>
// ---------------------------------------------------------------------------

EMSCRIPTEN_KEEPALIVE
extern "C" const char*
Neo3_SmartContract_Contract_CreateSignatureRedeemScript(const char* cs_in)
{
   std::string s_in(cs_in);
   // note that return stacked string pointer will "trust" emscripten to build JS-string for us
   std::string s_out = Neo::SmartContract::Contract::API_CreateSignatureRedeemScript(s_in);
   return s_out.c_str(); // ignore this warning, it works. TODO: find better solution.
}
