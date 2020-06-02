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
/////#include <lib-neopt-core/lib-neopt-core.h>
// ---------------------------------------------------------------------------

// ===================== MANUAL exports =====================

/*
EMSCRIPTEN_KEEPALIVE
extern "C" const char*
Neo3_SmartContract_Contract_CreateSignatureRedeemScript(const char* cs_in)
{
   std::string s_in(cs_in);
   // note that return stacked string pointer will "trust" emscripten to build JS-string for us
   std::string s_out = Neo::SmartContract::Contract::EXPORT_NEO3API_CreateSignatureRedeemScript(s_in);
   return s_out.c_str(); // ignore this warning, it works. TODO: find better solution.
}

EMSCRIPTEN_KEEPALIVE
extern "C" const char*
Neo3_SmartContract_scHelper_ToScriptHash(const char* cs_in)
{
   return Neo::SmartContract::scHelper::EXPORT_NEO3API_ToScriptHash(std::string(cs_in)).c_str();
}

// ===================== Wallets module =====================

EMSCRIPTEN_KEEPALIVE
extern "C" const char*
Neo3_Wallets_wHelper_ToAddress(const char* cs_in)
{
   return Neo::Wallets::wHelper::EXPORT_NEO3API_ToAddress(std::string(cs_in)).c_str();
}

EMSCRIPTEN_KEEPALIVE
extern "C" const char*
Neo3_Wallets_wHelper_ToScriptHash(const char* cs_in)
{
   return Neo::Wallets::wHelper::EXPORT_NEO3API_ToScriptHash(std::string(cs_in)).c_str();
}

*/

// begin automatically exported modules
