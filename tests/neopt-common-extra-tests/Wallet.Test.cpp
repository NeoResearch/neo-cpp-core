#include <iostream>
#include <limits> // numeric_limits

//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main()
#include "../thirdparty/catch2/catch.hpp"

// Some instructions for Catch2
// https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md

#include <iostream>

#include <neo3-cpp-core/Core.hpp>
//
#include <neo3-cpp-core/Cryptography/ECC/ECCurve.hpp>
//
#include <neo3-cpp-core/SmartContract/Contract.hpp>
#include <neo3-cpp-core/SmartContract/InteropService.Crypto.hpp>
#include <neo3-cpp-vm/OpCode.hpp>
#include <neo3-cpp-vm/ScriptBuilder.hpp>
//
#include <csbiginteger-cpp/src/csBigIntegerLibClass.hpp>
using BigInteger = csbigintegerlib::BigInteger;

using namespace std;
using namespace Neo::SmartContract;

// This test could already start from script - TODO
TEST_CASE("neopt extra tests - FromBigIntenger to ScriptHash")
{
   ECFieldElement X{ BigInteger{ "92417421609284060097852441734141491128266387380656748836951019715045385777354" }, *ECCurve::Secp256r1 };
   ECFieldElement Y{ BigInteger{ "81306213973968698003399946097148256829885864908442466985789085263601870844340" }, *ECCurve::Secp256r1 };
   ECPoint ecp{ X, Y, *ECCurve::Secp256r1 };
   vbyte vscript = Contract::CreateSignatureRedeemScript(ecp);
   UInt160 script_hash = Neo::SmartContract::scHelper::ToScriptHash(vscript);
   REQUIRE(script_hash.ToString() == "0x0eec9e10f6491c39f3e8dbc8af7186282487594a");

   const Neo::ProtocolSettings ps;
   string address = Neo::Wallets::wHelper::ToAddress(ps, script_hash);
   REQUIRE(address == "NSh6STZ6K4jUVDNZHwYSLc4ViuEm9Q1JtU");
}

TEST_CASE("neopt extra tests - Address(String) to ScriptHash(UInt160")
{
   string address = "NSh6STZ6K4jUVDNZHwYSLc4ViuEm9Q1JtU";
   UInt160 script_hash = Neo::Wallets::wHelper::ToScriptHash(address);
   REQUIRE(script_hash.ToString() == "0x0eec9e10f6491c39f3e8dbc8af7186282487594a");
}