//
// These are the C exports for library "neopt-core"
//
// =========================================================
// Functions marked as API in neo3-cpp-core are welcome here
// ---------------------------------------------------------
//
// Note that typically the function will receive a "string" parameter and return a "string"
//
// For compatibility reasons (on emscripten/wasm), in a first moment, we will return a copy of stacked
//   pointer string, that that won't cause "segfault", since emscripten will handle it.
//
// For the future, to achieve full compatibility between pure-C and JS environments, we would need to
//   find a solution that pleases 100% both C and WASM (maybe receiving "output" string as parameter,
//   like csbiginteger) but, for the moment, this is the best solution we have.
//

extern "C"
{
   // Neo::SmartContract::Contract::API_CreateSignatureRedeemScript(string) -> string;
   const char* Neo3_SmartContract_Contract_CreateSignatureRedeemScript(const char* cs_in);
}
