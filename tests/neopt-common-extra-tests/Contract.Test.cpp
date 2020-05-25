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
using namespace neopt;

TEST_CASE("neopt extra tests - Contract CreateSignatureRedeemScript from BigIntenger - I")
{
   ECFieldElement X{ BigInteger{ "43563478194357645732161043749214420341576583724275881899443933055754116882936" }, *ECCurve::Secp256r1 };
   ECFieldElement Y{ BigInteger{ "6800198406926458502571476951697947402787919362010374841430910815761615021861" }, *ECCurve::Secp256r1 };
   ECPoint ecp{ X, Y, *ECCurve::Secp256r1 };
   vbyte vscript = Contract::CreateSignatureRedeemScript(ecp);
   vbyte expectedVerification = { 12, 33, 3, 96, 80, 14, 12, 163, 115, 233, 65, 231, 174, 155, 203, 149, 91, 129, 86, 126, 183, 82, 81, 220, 101, 149, 154, 212, 175, 97, 250, 138, 177, 97, 248, 11, 65, 138, 107, 30, 117 };
   REQUIRE(vbyte == vbyte);
}
